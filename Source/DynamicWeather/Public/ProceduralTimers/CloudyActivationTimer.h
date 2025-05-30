// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
//#include "NiagaraComponent.h"
#include "CloudyActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FCloudyActivationTimer : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FCloudyActivationTimer() override
	{}
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Cloudy;
private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
