// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ProceduralDayTimer.generated.h"

class UDayTimer;
class ABaseDayActor;
class UProceduralDayTimerBuilder;

namespace UE::DaySequence
{
	// Utility function to simplify looking for owned components by type and name.
	template <typename T>
	T* GetComponentByName(AActor* InActor, FName Name)
	{
		for (T* Component : TInlineComponentArray<T*>(InActor))
		{
			if (Component->GetFName() == Name)
			{
				return Component;
			}
		}

		return nullptr;
	}
}
/**
 *
 */
USTRUCT(meta = (Hidden), Blueprintable, BlueprintType)
struct FProceduralDayTimer
{
	GENERATED_BODY()

    FProceduralDayTimer() {}
    FProceduralDayTimer(const FProceduralDayTimer&) = default;
    FProceduralDayTimer& operator=(const FProceduralDayTimer&) = default;
    FProceduralDayTimer(FProceduralDayTimer&&) = default;
    FProceduralDayTimer& operator=(FProceduralDayTimer&&) = default;
    virtual ~FProceduralDayTimer()
    {}

	UDayTimer* GetSequence(ABaseDayActor* InActor);
	virtual void OnDayTimerEvent(float CurrentTimeOfDay) {};

	// UPROPERTY(EditAnywhere, Category="Day Sequence")
	// FDaySequenceConditionSet Conditions;

protected:

	/** 타이머 값들 설정하는 곳*/
	virtual void BuildSequence(UProceduralDayTimerBuilder* InBuilder) {}


public:
	TWeakObjectPtr<ABaseDayActor> WeakTargetActor = nullptr;
};
