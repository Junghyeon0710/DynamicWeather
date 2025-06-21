// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralTimers/NiagaraActivationTimerBase.h"
//#include "NiagaraComponent.h"
#include "CloudyActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FCloudyActivationTimer : public FNiagaraActivationTimerBase
{
	GENERATED_BODY()

	virtual ~FCloudyActivationTimer() override
	{}
protected:

private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
//	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
