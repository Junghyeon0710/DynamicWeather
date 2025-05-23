// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProceduralDayTimerBuilder.generated.h"

class ABaseDayActor;
class UDayTimer;
/**
 * 
 */
UCLASS()
class DYNAMICWEATHER_API UProceduralDayTimerBuilder : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Day Sequence")
	UDayTimer* Initialize(ABaseDayActor* InActor, UDayTimer* InitialTimer = nullptr, bool bClearInitialSequence = true);

	UDayTimer* GetDayTimer();
private:

	TObjectPtr<UDayTimer> ProceduralDayTimer = nullptr;

	TObjectPtr<ABaseDayActor> TargetActor = nullptr;
};
