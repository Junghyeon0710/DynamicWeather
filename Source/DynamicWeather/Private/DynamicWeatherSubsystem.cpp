// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicWeatherSubsystem.h"
#include "Actors/BaseDayActor.h"

#include "EngineUtils.h"

void UDynamicWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDynamicWeatherSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

ABaseDayActor* UDynamicWeatherSubsystem::GetDaySequenceActor(bool bFindFallbackOnNull) const
{
	if (ABaseDayActor* CurrentDaySequenceActor = DayActor.Get())
	{
		return CurrentDaySequenceActor;
	}

	if (bFindFallbackOnNull)
	{
		// Fallback to iterating over all DayActors in the world and returning
		// the first match.
		TActorIterator<ABaseDayActor> It(GetWorld());
		return It ? *It : nullptr;
	}

	return nullptr;
}

void UDynamicWeatherSubsystem::SetDaySequenceActor(ABaseDayActor* InActor)
{
	DayActor = InActor;
	BroadcastOnDayActorSet(InActor);
}

void UDynamicWeatherSubsystem::BroadcastOnDayActorSet(ABaseDayActor* InActor) const
{
	OnDayActorSet.Broadcast(InActor);
	OnDayActorSetEvent.Broadcast(InActor);
}
