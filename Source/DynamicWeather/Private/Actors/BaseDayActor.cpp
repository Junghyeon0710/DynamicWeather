// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseDayActor.h"

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

// Called when the game starts or when spawned
void ABaseDayActor::BeginPlay()
{
	Super::BeginPlay();
	
}


