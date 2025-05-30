// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTimers/CloudyActivationTimer.h"

void FCloudyActivationTimer::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{
	FProceduralDayTimer::BuildSequence(InBuilder);
}

void FCloudyActivationTimer::OnDayTimerEvent(float CurrentTimeOfDay)
{
}
