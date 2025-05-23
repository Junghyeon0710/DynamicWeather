// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseDayActor.h"

#include "DayTimer.h"
#include "DayTimerCollectionAsset.h"
#include "DynamicWeatherSubsystem.h"
#include "InstancedStruct.h"
#include "ProceduralDayTimer.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABaseDayActor::ABaseDayActor(const FObjectInitializer& Init) : Super(Init)
{
	USceneComponent* SceneRootComponent = CreateDefaultSubobject<USceneComponent>(USceneComponent::GetDefaultSceneRootVariableName());
	SetRootComponent(SceneRootComponent);
	
	SunRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SunRoot"));
	SunRootComponent->SetupAttachment(RootComponent);
	
	SunComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Sun"));
	SunComponent->SetupAttachment(SunRootComponent);
	
	ExponentialHeightFogComponent = CreateOptionalDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
	ExponentialHeightFogComponent->SetupAttachment(RootComponent);
	ExponentialHeightFogComponent->bEnableVolumetricFog = true;

	SkyAtmosphereComponent = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
	SkyAtmosphereComponent->SetupAttachment(RootComponent);

	SkyLightComponent = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLightComponent->SetupAttachment(RootComponent);
	SkyLightComponent->bRealTimeCapture = true;
	SkyLightComponent->bLowerHemisphereIsBlack = false;

	VolumetricCloudComponent = CreateOptionalDefaultSubobject<UVolumetricCloudComponent>(TEXT("VolumetricCloud"));
	VolumetricCloudComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SkySphereDefaultMesh(TEXT("/Engine/EngineSky/SM_SkySphere.SM_SkySphere"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SkySphereDefaultMaterial(TEXT("/Engine/EngineSky/M_SimpleSkyDome.M_SimpleSkyDome"));
	SkySphereComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("SkySphere"));
	SkySphereComponent->SetupAttachment(RootComponent);
	SkySphereComponent->SetStaticMesh(SkySphereDefaultMesh.Object);
	SkySphereComponent->SetMaterial(0, SkySphereDefaultMaterial.Object.Get());
	SkySphereComponent->SetRelativeScale3D(FVector(400.f));
}

float ABaseDayActor::GetTimePerCycleToSeconds() const
{
	return TimePerCycle.ToSeconds();
}

float ABaseDayActor::GetDayLengthToSeconds() const
{
	return DayLength.ToSeconds();
}

float ABaseDayActor::GetInitialTimeOfDayToSeconds() const
{
	return InitialTimeOfDay.ToSeconds();
}

// Called when the game starts or when spawned
void ABaseDayActor::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		if (UDynamicWeatherSubsystem* DynamicWeatherSubsystem = World->GetSubsystem<UDynamicWeatherSubsystem>())
		{
			DynamicWeatherSubsystem->SetDaySequenceActor(this);
		}
	}

	InitializeDayTimers();
}

void ABaseDayActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (const UWorld* World = GetWorld())
	{
		if (UDynamicWeatherSubsystem* DynamicWeatherSubsystem = World->GetSubsystem<UDynamicWeatherSubsystem>())
		{
			if (DynamicWeatherSubsystem->GetDaySequenceActor(/* bFindFallbackOnNull */ false) != this)
			{
				DynamicWeatherSubsystem->SetDaySequenceActor(this);
			}
		}
	}
}

void ABaseDayActor::InitializeDayTimers()
{
	
	for (UDayTimerCollectionAsset* Collection : DaySequenceCollections)
	{
		if (!Collection)
		{
			continue;
		}
		
		for (TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence : Collection->ProceduralDayTimers)
		{
			if (!ProceduralDaySequence.IsValid())
			{
				continue;
			}

			FProceduralDayTimer& ProceduralSequence = ProceduralDaySequence.GetMutable<FProceduralDayTimer>();
 
			if (UDayTimer* Timer = ProceduralSequence.GetSequence(this))
			{
				Collection->Timer = Timer;
				Timer->SetTimerDelegate(ProceduralDaySequence);
				Timer->StartDayTimer();
				//InitializeDaySequence(Timer);
			}
		}
	}
}


