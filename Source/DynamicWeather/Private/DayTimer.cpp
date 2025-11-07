// Fill out your copyright notice in the Description page of Project Settings.


#include "DayTimer.h"

#include "InstancedStruct.h"
#include "Actors/BaseDayActor.h"

float UDayTimer::ElapsedWeatherTime = 0.f;

void UDayTimer::SetTimerDelegate(const TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence)
{
	TimerStructs.Empty();
	TimerStructs.Add(ProceduralDaySequence);
}

void UDayTimer::SetTimerDelegates(const TArray<TInstancedStruct<FProceduralDayTimer>>& ProceduralDaySequences)
{
	TimerStructs = ProceduralDaySequences;
}

float UDayTimer::GetVirtualSecondsFromRealSeconds(float RealSeconds) const
{
	return (RealSeconds / TimerLength) * VirtualDaySeconds;
}

void UDayTimer::StartDayTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DayTimer);
    bTimerSetupComplete= true;
	//ElapsedTime = FMath::Clamp(ElapsedTime - TimerLength, 0, TimerLength);

	GetWorld()->GetTimerManager().SetTimer(DayTimer,this,&UDayTimer::OnDayTimer,TimerRate,true);
}

void UDayTimer::OnDayTimer()
{
	ElapsedTime += TimerRate;
    ElapsedWeatherTime += TimerRate;

    const float VirtualElapsedWeatherTime = GetVirtualSecondsFromRealSeconds(ElapsedWeatherTime);

    if(VirtualElapsedWeatherTime >= WeatherCycleTime)
    {
        DayActor->InitializeCurrentSeasonWeather();
        ElapsedWeatherTime = 0.f;
    }

	if(ElapsedTime > TimerLength)
	{
		if (InitTime == 0)
		{
			DayActor->NextDay();
		}
		//종료 알림
	    ElapsedTime = FMath::Clamp(ElapsedTime - TimerLength, 0, TimerLength);
		OnTimerCompleted.Broadcast();
		bTimerSetupComplete = true;

		return;
	}

	/** 초기시간부터 시작합니다 */
	const float VirtualHours = GetVirtualSecondsFromRealSeconds(ElapsedTime) / 3600.0f;
	float VirtualTime = VirtualHours + InitTime;

	if(VirtualTime > 24)
	{
		VirtualTime -=24;
		if(bTimerSetupComplete)
		{
			DayActor->NextDay();
			bTimerSetupComplete =! bTimerSetupComplete;
		}
	}
	for (TInstancedStruct<FProceduralDayTimer>& TimerStruct : TimerStructs)
	{
		if (TimerStruct.IsValid())
		{
			FProceduralDayTimer& Timer = TimerStruct.GetMutable<FProceduralDayTimer>();
			Timer.OnDayTimerEvent(VirtualTime);
		}
	}

	OnTimerUpdatedFromHours.Broadcast(VirtualTime);
}

void UDayTimer::SetDayActor(ABaseDayActor* InDayActor)
{
	DayActor = InDayActor;
}

void UDayTimer::AdvanceHours(int32 InHours)
{
    float VirtualSeconds = InHours * 3600.0f;

    float RealDelta = (VirtualSeconds / VirtualDaySeconds) * TimerLength;

    ElapsedTime += RealDelta;

    const float VirtualHours = GetVirtualSecondsFromRealSeconds(ElapsedTime) / 3600.0f;
    float VirtualTime = VirtualHours + InitTime;

    if(VirtualTime > 24)
    {
        VirtualTime -=24;
    }

	OnTimerUpdatedFromHours.Broadcast(VirtualTime);

}
