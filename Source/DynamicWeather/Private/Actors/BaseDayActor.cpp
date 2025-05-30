// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseDayActor.h"

#include "DayTimer.h"
#include "DayTimerCollectionAsset.h"
#include "DynamicWeatherSubsystem.h"
#include "InstancedStruct.h"
#include "ProceduralDayTimer.h"
#include "SeasonWeatherDataAsset.h"
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

UDayTimer* ABaseDayActor::GetCurrentDayTimer() const
{
	if(CurrentTimer)
	{
		return CurrentTimer;
	}
	return nullptr;
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

float ABaseDayActor::GetInitialTimeOfDayToHour() const
{
	return InitialTimeOfDay.ToHours();
}

void ABaseDayActor::SetCurrentTimeFromSeconds(float Seconds)
{
	CurrentTime = FDynamicWeatherTime::FromSeconds(Seconds);
}

void ABaseDayActor::SetCurrentTimeFromHours(float Hours)
{
	CurrentTime = FDynamicWeatherTime::FromHours(Hours);
}

void ABaseDayActor::AdvanceDay()
{
	CurrentDayOfYear++;
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

	//InitializeDayTimers();
	InitializeSeasonWeatherTimer();
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
				CurrentTimer = Timer;
				Timer->SetTimerDelegate(ProceduralDaySequence);
				Timer->StartDayTimer();
				//InitializeDaySequence(Timer);
			}
		}
	}
}

void ABaseDayActor::InitializeSeasonWeatherTimer()
{
	if(!SeasonWeatherDataAsset)
	{
		return;
	}

	if(SeasonWeatherDataAsset->SeasonWeatherInfos.IsEmpty())
	{
		return;
	}

	const TArray<FSeasonWeatherInfo>& SeasonWeatherInfos = SeasonWeatherDataAsset->SeasonWeatherInfos;

	for(const FSeasonWeatherInfo& Info : SeasonWeatherInfos)
	{
		//// 현재 일수는 이 Info의 기간 안에 있음
		if (CurrentDayOfYear >= Info.StartDay && CurrentDayOfYear < Info.StartDay + Info.Duration)
		{
			CurrentSeason = Info.SeasonName.ToString();
			
			FWeatherProbability SelectedWeather = Info.GetRandomWeather();

			CurrentWeatherType = SelectedWeather.WeatherType;

			TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence = SelectedWeather.ProceduralDayTimers;
		
			if (!ProceduralDaySequence.IsValid())
			{
				return;
			}

			FProceduralDayTimer& ProceduralSequence = ProceduralDaySequence.GetMutable<FProceduralDayTimer>();
			
			if(!ProceduralSequence.WeakTargetActor.Get())
			{
				ProceduralSequence.WeakTargetActor = this; // 바꾸기 권장..
			}
		
			if(!CurrentTimer)
			{
				if (UDayTimer* Timer = ProceduralSequence.GetSequence(this))
				{
					CurrentTimer = Timer;
					CurrentTimer->SetDayActor(this);
					CurrentTimer->OnTimerCompleted.AddDynamic(this,&ThisClass::InitializeSeasonWeatherTimer);
					CurrentTimer->OnTimerUpdatedFromHours.AddDynamic(this,&ThisClass::SetCurrentTimeFromHours);
				}
			}
			CurrentTimer->SetTimerDelegate(ProceduralDaySequence);
			CurrentTimer->StartDayTimer();
			
			return;
		}
	}
}


