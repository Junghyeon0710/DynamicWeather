﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SunMoonDayActor.h"

#include "Components/DirectionalLightComponent.h"

ASunMoonDayActor::ASunMoonDayActor(const FObjectInitializer& Init) : Super(Init)
{
	MoonComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Moon"));
	MoonComponent->SetupAttachment(SunRootComponent);

	// Give Sun forward shading priority.
	SunComponent->SetForwardShadingPriority(1);
	MoonComponent->SetForwardShadingPriority(0);

	// Configure other Moon defaults.
	MoonComponent->SetAtmosphereSunLightIndex(1);	// Make Moon the secondary directional light that contributes to the sky atmosphere.
	MoonComponent->SetIntensity(0.05f);
	MoonComponent->SetUseTemperature(true);
	MoonComponent->SetTemperature(9000.f);
	MoonComponent->SetWorldRotation(FRotator(-45.f, 0.f, 0.f));
	
	// Override the sky sphere material.
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SkySphereDefaultMaterial(TEXT("/DaySequence/MI_24hrSky.MI_24hrSky"));
	SkySphereComponent->SetMaterial(0, SkySphereDefaultMaterial.Object.Get());
	
}



