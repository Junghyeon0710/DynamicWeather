// Fill out your copyright notice in the Description page of Project Settings.


#include "DayTimer.h"

#include "InstancedStruct.h"

void UDayTimer::SetTimerDelegate(const TInstancedStruct<FProceduralDayTimer>& ProceduralDaySequence)
{
	TimerStruct = ProceduralDaySequence;
}

float UDayTimer::GetVirtualSecondsFromRealSeconds(int32 RealSeconds) const
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
	TimerRate += TimerRate;
	
	if(TimerRate>TimerLength)
	{
		//종료 알림

		return;
	}

	/** 초기시간부터 시작합니다 */
	const float VirtualTime = TimerRate + InitTime;
	TimerStruct.GetMutable<FProceduralDayTimer>().OnDayTimerEvent(GetVirtualSecondsFromRealSeconds(VirtualTime));
}
