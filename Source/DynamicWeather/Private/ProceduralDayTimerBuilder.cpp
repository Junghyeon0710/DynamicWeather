// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\ProceduralDayTimerBuilder.h"

#include "DayTimer.h"
#include "Actors/BaseDayActor.h"

UDayTimer* UProceduralDayTimerBuilder::Initialize(ABaseDayActor* InActor, UDayTimer* InitialTimer,bool bClearInitialSequence)
{
	if (!ensureAlways(!TargetActor) || !ensureAlways(InActor))
	{
		return nullptr;
	}

	TargetActor = InActor;

	if (InitialTimer)
	{
		ProceduralDayTimer = InitialTimer;
		if (bClearInitialSequence)
		{
			//ClearKeys();
		}
	}
	else
	{
		const FName TimerName = MakeUniqueObjectName(InActor, UDayTimer::StaticClass());
		ProceduralDayTimer = NewObject<UDayTimer>(InActor, TimerName, RF_Transient);
		//ProceduralDayTimer->Initialize(RF_Transient);

	}

	const float DaySeconds = TargetActor->GetTimePerCycleToSeconds();
	const float DayLength = TargetActor->GetDayLengthToSeconds();
	const float InitTime = TargetActor->GetInitialTimeOfDayToHour();
    const float WeatherChangeInterval = TargetActor->GetWeatherChangeInterval();
	ProceduralDayTimer->SetTimerLength(DaySeconds);
	ProceduralDayTimer->SetVirtualDaySeconds(DayLength);
	ProceduralDayTimer->SetInitTime(InitTime);
    ProceduralDayTimer->SetWeatherCycleTime(WeatherChangeInterval);

	return ProceduralDayTimer;
}

UDayTimer* UProceduralDayTimerBuilder::GetDayTimer()
{
	if(ProceduralDayTimer)
	{
		return ProceduralDayTimer;
	}
	return nullptr;
}
