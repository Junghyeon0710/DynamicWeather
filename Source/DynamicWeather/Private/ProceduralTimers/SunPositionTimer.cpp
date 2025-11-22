// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTimers/SunPositionTimer.h"

#include "DayTimer.h"
#include "Actors/BaseDayActor.h"
#include "Components/DirectionalLightComponent.h"
#include "Curves/CurveVector.h"
#include "Kismet/GameplayStatics.h"

void FSunPosition::BuildSequence(UProceduralDayTimerBuilder* InBuilder)
{

}

void FSunPosition::OnDayTimerEvent(float CurrentTimeOfDay)
{
	using namespace UE::DaySequence;

	ABaseDayActor* TargetActor = WeakTargetActor.Get();

//	UE_LOG(LogTemp, Error, TEXT("CurrentTimeOfDay , %f"), CurrentTimeOfDay);
	if (!TargetActor)
	{
		return;;
	}

	if (UDirectionalLightComponent* SunComponent = GetComponentByName<UDirectionalLightComponent>(TargetActor, SunComponentName))
	{
		if(SunPositionCurve)
		{
			const FVector CurveValue = SunPositionCurve->GetVectorValue(CurrentTimeOfDay);
			//float SunPitch = SunPositionCurve->GetFloatValue(CurrentTimeOfDay);
			//UE_LOG(LogTemp, Error, TEXT("SunPitch , %f"), SunPitch);
			// Yaw는 유지하고 Pitch만 변경
			const FRotator NewRotation = FRotator(CurveValue.Y, CurveValue.Z, CurveValue.X);
			const FRotator LerpRotation = FMath::Lerp(SunComponent->GetRelativeRotation(),NewRotation,8.f);
			SunComponent->SetRelativeRotation(NewRotation);
			//UE_LOG(LogTemp, Error, TEXT("%s"), *SunComponent->GetComponentRotation().ToString());
		}
	}
}

