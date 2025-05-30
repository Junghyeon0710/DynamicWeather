// Fill out your copyright notice in the Description page of Project Settings.


#include "DayTimer.h"

#include "InstancedStruct.h"
#include "Actors/BaseDayActor.h"

void UDayTimer::SetTimerDelegate(const TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence)
{
	TimerStruct = ProceduralDaySequence;
}

float UDayTimer::GetVirtualSecondsFromRealSeconds(float RealSeconds) const
{
	return (RealSeconds / TimerLength) * VirtualDaySeconds;
}

void UDayTimer::StartDayTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DayTimer);
	
	GetWorld()->GetTimerManager().SetTimer(DayTimer,this,&UDayTimer::OnDayTimer,TimerRate,true);	
}

void UDayTimer::OnDayTimer()
{
	ElapsedTime += TimerRate;
	
	if(ElapsedTime>TimerLength)
	{
		//종료 알림
		ElapsedTime = 0;
		OnTimerCompleted.Broadcast();
		bTimerSetupComplete = true;
		return;
	}

	/** 초기시간부터 시작합니다 */
	//	const float VirtualTime = TimerRate + InitTime;
	const float VirtualHours = GetVirtualSecondsFromRealSeconds(ElapsedTime) / 3600.0f;
	float VirtualTime = VirtualHours + InitTime;

	if(VirtualTime >24)
	{
		VirtualTime -=24;
		if(bTimerSetupComplete)
		{
			DayActor->AdvanceDay();
			bTimerSetupComplete =! bTimerSetupComplete;
		}
	}
	TimerStruct.GetMutable<FProceduralDayTimer>().OnDayTimerEvent(VirtualTime);

	OnTimerUpdatedFromHours.Broadcast(VirtualTime);
}

void UDayTimer::SetDayActor(ABaseDayActor* InDayActor)
{
	DayActor = InDayActor;
}
