// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DynamicWeatherSubsystem.generated.h"
class ABaseDayActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDayActorSet, ABaseDayActor*, NewActor);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDayActorSetEvent, ABaseDayActor*)


/**
 * 
 */
UCLASS()
class DYNAMICWEATHER_API UDynamicWeatherSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category=DaySequence)
	ABaseDayActor* GetDaySequenceActor(bool bFindFallbackOnNull = true) const;

	UFUNCTION(BlueprintCallable, Category=DaySequence)
	void SetDaySequenceActor(ABaseDayActor* InActor);

public:

	/** Blueprint exposed delegate that is broadcast when the active DayActor changes. */
	UPROPERTY(BlueprintAssignable, Category=DaySequence)
	FOnDayActorSet OnDayActorSet;

	/** Natively exposed delegate that is broadcast when the active DayActor changes. */
	FOnDayActorSetEvent OnDayActorSetEvent;
private:
	void BroadcastOnDayActorSet(ABaseDayActor* InActor) const;
	
	TWeakObjectPtr<ABaseDayActor> DayActor;
};
