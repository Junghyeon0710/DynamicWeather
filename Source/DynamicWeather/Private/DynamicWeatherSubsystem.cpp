// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicWeatherSubsystem.h"
#include "Actors/BaseDayActor.h"

#include "EngineUtils.h"

UDynamicWeatherSubsystem* UDynamicWeatherSubsystem::Get(const UObject* WorldContextObject)
{
    if (GEngine)
    {
        UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

        return World->GetSubsystem<UDynamicWeatherSubsystem>();
    }

    return nullptr;
}

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

void UDynamicWeatherSubsystem::HandleDayChange(int32 InYear, int32 InDay,const FString& InSeason, EWeatherType InWeather) const
{
	OnDayChanged.Broadcast(InYear,InDay,InSeason,InWeather);
}

bool UDynamicWeatherSubsystem::IsRaining() const
{
    if (DayActor.IsValid())
    {
	    return DayActor->IsRaining();
    }
    return false;
}

EWeatherType UDynamicWeatherSubsystem::GetWeatherType() const
{
    if (DayActor.IsValid())
    {
        return DayActor->GetWeatherType();
    }

    return EWeatherType::None;
}

void UDynamicWeatherSubsystem::HandleAdvanceTime(int32 InhHours)
{
    if (DayActor.IsValid())
    {
        DayActor->AdvanceTime(InhHours);
    }
}

void UDynamicWeatherSubsystem::HandleNextDay()
{
    if (DayActor.IsValid())
    {
        DayActor->NextDay();
    }
}

void UDynamicWeatherSubsystem::BroadcastOnDayActorSet(ABaseDayActor* InActor) const
{
	OnDayActorSet.Broadcast(InActor);
	OnDayActorSetEvent.Broadcast(InActor);
}
