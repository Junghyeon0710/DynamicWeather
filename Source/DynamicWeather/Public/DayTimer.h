// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralDayTimer.h"
#include "InstancedStruct.h"
#include "UObject/Object.h"
#include "DayTimer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdatedFromHours, float, CurrentTimeInHours);
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
    void SetWeatherCycleTime(float InWeatherLength) {WeatherCycleTime = InWeatherLength;}

	void SetTimerDelegate(const TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence);
	void SetTimerDelegates(const TArray<TInstancedStruct<FProceduralDayTimer>>& ProceduralDaySequences);
	float GetVirtualSecondsFromRealSeconds(float RealSeconds) const;

	void StartDayTimer();
	UFUNCTION()
	void OnDayTimer();

	void SetDayActor(ABaseDayActor* InDayActor);
    void AdvanceHours(int32 InHours);

public:
	UPROPERTY(BlueprintAssignable,Category = Timer)
	FOnTimerCompleted OnTimerCompleted;

	UPROPERTY(BlueprintAssignable,Category = Timer)
	FOnTimerUpdatedFromHours OnTimerUpdatedFromHours;

private:

	float TimerLength;
	float TimerRate = 0.1;
	float ElapsedTime = 0.0f;
	float InitTime;
	float VirtualDaySeconds;
    float WeatherCycleTime;
    float ElapsedWeatherTime = 0.f;
	bool bTimerSetupComplete = true;

	FTimerHandle DayTimer;

	TArray<TInstancedStruct<FProceduralDayTimer>> TimerStructs;
	FProceduralDayTimer ProceduralDayTimer;

	UPROPERTY()
	TObjectPtr<ABaseDayActor> DayActor;
};
