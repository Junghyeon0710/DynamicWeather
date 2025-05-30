﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
//#include "NiagaraComponent.h"
#include "SnowActivationTimer.generated.h"

class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FSnowActivationTimer : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FSnowActivationTimer() override
	{}
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Snow;
private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
};
