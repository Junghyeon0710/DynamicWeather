// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\ProceduralDayTimer.h"

#include "ProceduralDayTimerBuilder.h"
#include "Actors/BaseDayActor.h"

UDayTimer* FProceduralDayTimer::GetSequence(ABaseDayActor* InActor)
{
	WeakTargetActor = InActor;
	
	UDayTimer* ProceduralSequence = nullptr;
	
	if (InActor)
	{
		UProceduralDayTimerBuilder* SequenceBuilder = NewObject<UProceduralDayTimerBuilder>();
		ProceduralSequence = SequenceBuilder->Initialize(InActor,InActor->GetCurrentDayTimer());
	}
	
	return ProceduralSequence;
}


