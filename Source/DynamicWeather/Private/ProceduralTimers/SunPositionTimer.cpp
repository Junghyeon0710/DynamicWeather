// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTimers/SunPositionTimer.h"

#include "DayTimer.h"
#include "Actors/BaseDayActor.h"
#include "Components/DirectionalLightComponent.h"

void FSunPosition::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{
	
}

void FSunPosition::OnDayTimerEvent(float CurrentTimeOfDay)
{
	using namespace UE::DaySequence;

	ABaseDayActor* TargetActor = WeakTargetActor.Get();
	
	if (!TargetActor)
	{
		return;
	}
	
	if (UDirectionalLightComponent* SunComponent = GetComponentByName<UDirectionalLightComponent>(TargetActor, SunComponentName))
	{
		if(SunPositionCurve)
		{
			float SunPitch = SunPositionCurve->GetFloatValue(CurrentTimeOfDay);

			// Yaw는 유지하고 Pitch만 변경
			const FRotator NewRotation = FRotator(SunPitch, SunComponent->GetComponentRotation().Yaw, 0.f);
			SunComponent->SetWorldRotation(NewRotation);
			UE_LOG(LogTemp, Error, TEXT("%s"), *SunComponent->GetComponentRotation().ToString());
		}
	}
}

