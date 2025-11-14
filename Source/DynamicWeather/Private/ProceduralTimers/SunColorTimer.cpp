// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTimers/SunColorTimer.h"

#include "Actors/BaseDayActor.h"
#include "Components/DirectionalLightComponent.h"
#include "Curves/CurveLinearColor.h"

void FSunColorTimer::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{
}

void FSunColorTimer::OnDayTimerEvent(float CurrentTimeOfDay)
{
    using namespace UE::DaySequence;

    ABaseDayActor* TargetActor = WeakTargetActor.Get();

    if (!TargetActor)
    {
        return;;
    }

    if (UDirectionalLightComponent* SunComponent = GetComponentByName<UDirectionalLightComponent>(TargetActor, SunComponentName))
    {
        if(SunColorCurve)
        {
            const FLinearColor SunColor = SunColorCurve->GetLinearColorValue(CurrentTimeOfDay);
            SunComponent->SetLightColor(SunColor);
        }
    }
}
