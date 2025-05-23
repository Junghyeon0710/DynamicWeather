// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
#include "SunPositionTimer.generated.h"

/**
 * 
 */
USTRUCT()
struct FSunPosition : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FSunPosition() override
	{}

	UPROPERTY(EditAnywhere, Category = "Procedural Parameters")
	FName SunComponentName = FName(TEXT("Sun"));
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "SunPosition")
	TObjectPtr<UCurveFloat> SunPositionCurve;
private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;

	
};
