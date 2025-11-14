// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
#include "SunColorTimer.generated.h"

/**
 *
 */
USTRUCT()
struct FSunColorTimer : public FProceduralDayTimer
{
    GENERATED_BODY()

    virtual ~FSunColorTimer() override
    {}

    UPROPERTY(EditAnywhere, Category = "Procedural Parameters")
    FName SunComponentName = FName(TEXT("Sun"));

protected:

    UPROPERTY(EditDefaultsOnly, Category = "SunColor")
    TObjectPtr<UCurveLinearColor> SunColorCurve;
private:
    virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
    virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;


};
