// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralDayTimer.h"
#include "Engine/DataAsset.h"
#include "InstancedStruct.h"
#include "DayTimerCollectionAsset.generated.h"

class UDayTimer;
/**
 *
 */
UCLASS()
class DYNAMICWEATHER_API UDayTimerCollectionAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="Day Timer")
	TObjectPtr<UDayTimer> Timer;

	UPROPERTY(EditAnywhere, Category="Day Timer", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FProceduralDayTimer>> ProceduralDayTimers;
};
