// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
#include "SnowActivationTimer.generated.h"

/**
 * 
 */
USTRUCT()
struct FSnowActivationTimer : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FSnowActivationTimer() override
	{}

private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
};
