// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraActivationTimerBase.h"
//#include "NiagaraComponent.h"
#include "HeavyRainActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FHeavyRainActivationTimer : public FNiagaraActivationTimerBase
{
	GENERATED_BODY()

	virtual ~FHeavyRainActivationTimer() override
	{}
protected:

private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	//virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
