// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SeasonWeatherData.h"
#include "Subsystems/WorldSubsystem.h"
#include "DynamicWeatherSubsystem.generated.h"
class ABaseDayActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDayActorSet, ABaseDayActor*, NewActor);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDayActorSetEvent, ABaseDayActor*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDayChanged, int32, Year, int32,Day,const FString&, Season,  EWeatherType, Weather);


/**
 *
 */
UCLASS()
class DYNAMICWEATHER_API UDynamicWeatherSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
    static UDynamicWeatherSubsystem* Get(const UObject* WorldContextObject);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category=DaySequence)
	ABaseDayActor* GetDaySequenceActor(bool bFindFallbackOnNull = true) const;

	UFUNCTION(BlueprintCallable, Category=DaySequence)
	void SetDaySequenceActor(ABaseDayActor* InActor);

	UFUNCTION()
	void HandleDayChange(int32 InYear, int32 InDay,const FString& InSeason,  EWeatherType InWeather) const;

	UFUNCTION(BlueprintCallable, Category=DaySequence)
	bool IsRaining() const;

    UFUNCTION(BlueprintCallable, Category = "Weather")
    EWeatherType GetWeatherType() const;

    UFUNCTION(BlueprintCallable, Category = "Weather")
    FString GetCurrentTime() const;

    UFUNCTION(BlueprintCallable, Category = "Weather")
    FString GetCurrentSeason() const;

    UFUNCTION(BlueprintCallable, Category = "Weather")
    FString GetCurrentDayOfWeek() const;

public:
    UFUNCTION(BlueprintCallable, Category = "Weather")
    void HandleAdvanceTime(int32 InhHours);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void HandleNextDay();

public:

	/** Blueprint exposed delegate that is broadcast when the active DayActor changes. */
	UPROPERTY(BlueprintAssignable, Category=DaySequence)
	FOnDayActorSet OnDayActorSet;

	/** Natively exposed delegate that is broadcast when the active DayActor changes. */
	FOnDayActorSetEvent OnDayActorSetEvent;

	UPROPERTY(BlueprintAssignable)
	FOnDayChanged OnDayChanged;
private:
	void BroadcastOnDayActorSet(ABaseDayActor* InActor) const;

	TWeakObjectPtr<ABaseDayActor> DayActor;
};
