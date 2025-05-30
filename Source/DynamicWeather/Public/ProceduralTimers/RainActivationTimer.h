// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
//#include "NiagaraComponent.h"
#include "RainActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FRainActivationTimer : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FRainActivationTimer() override
	{}
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Rain;
private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
