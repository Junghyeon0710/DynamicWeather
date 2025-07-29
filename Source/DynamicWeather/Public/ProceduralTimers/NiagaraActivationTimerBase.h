// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ProceduralDayTimer.h"
//#include "NiagaraComponent.h"
#include "NiagaraActivationTimerBase.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
/**
 * 
 */
USTRUCT()
struct FNiagaraActivationTimerBase : public FProceduralDayTimer
{
	GENERATED_BODY()

	virtual ~FNiagaraActivationTimerBase() override
	{}

	//void DeActivateNiagara() const;
	UNiagaraSystem* GetNiagaraSystem() const { return NiagaraSystem; };
protected:

	// UPROPERTY()
	// TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> NiagaraSystem;
	

	
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) override;
private:
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) override;
	
};
