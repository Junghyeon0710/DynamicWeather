// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTimers/HeavyRainActivationTimer.h"

void FHeavyRainActivationTimer::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{
	FProceduralDayTimer::BuildSequence(InBuilder);
}

void FHeavyRainActivationTimer::OnDayTimerEvent(float CurrentTimeOfDay)
{

}
