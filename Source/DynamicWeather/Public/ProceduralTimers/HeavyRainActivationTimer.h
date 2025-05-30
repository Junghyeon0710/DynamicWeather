// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
//#include "NiagaraComponent.h"
#include "HeavyRainActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FHeavyRainActivationTimer : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FHeavyRainActivationTimer() override
	{}
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> HeavyRain;
private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
