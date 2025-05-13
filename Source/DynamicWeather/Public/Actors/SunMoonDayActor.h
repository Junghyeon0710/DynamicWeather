// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDayActor.h"
#include "SunMoonDayActor.generated.h"
class UDirectionalLightComponent;

UCLASS()
class DYNAMICWEATHER_API ASunMoonDayActor : public ABaseDayActor
{
	GENERATED_BODY()

public:
	ASunMoonDayActor(const FObjectInitializer& Init);

protected:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDirectionalLightComponent> MoonComponent;
};
