// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "ProceduralDayTimer.h"
#include "UObject/Object.h"
#include "DayTimer.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMICWEATHER_API UDayTimer : public UObject
{
	GENERATED_BODY()

public:
	void SetTimerLength(float InTimerLength) {TimerLength = InTimerLength;}
	void SetVirtualDaySeconds(float InVirtualDaySeconds) {VirtualDaySeconds = InVirtualDaySeconds;}
	void SetInitTime(float InInitTime) {InitTime = InInitTime;}
	
	void SetTimerDelegate(const TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence);
	float GetVirtualSecondsFromRealSeconds(int32 RealSeconds) const;

	void StartDayTimer();
	UFUNCTION()
	void OnDayTimer();
private:
	
	float TimerLength;
	float TimerRate = 0.1;
	float InitTime;
	int32 VirtualDaySeconds;

	FTimerHandle DayTimer;

	TInstancedStruct<FProceduralDayTimer> TimerStruct;
	FProceduralDayTimer ProceduralDayTimer;
};
