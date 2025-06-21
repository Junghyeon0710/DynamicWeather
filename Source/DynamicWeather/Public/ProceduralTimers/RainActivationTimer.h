// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraActivationTimerBase.h"
//#include "NiagaraComponent.h"
#include "RainActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FRainActivationTimer : public FNiagaraActivationTimerBase
{
	GENERATED_BODY()

	virtual ~FRainActivationTimer() override
	{}
protected:

private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	//virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
