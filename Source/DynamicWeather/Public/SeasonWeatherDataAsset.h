// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralDayTimer.h"
#include "Engine/DataAsset.h"
#include "SeasonWeatherData.h"
#include "InstancedStruct.h"
#include "SeasonWeatherDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWeatherProbability
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeatherType WeatherType;

	UPROPERTY(EditAnywhere, Category="Day Timer", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FProceduralDayTimer>> ProceduralDayTimers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Probability; // e.g. 50.0 for 50%   a a
};

USTRUCT(BlueprintType)
struct FSeasonWeatherInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SeasonName;  // "Spring", "Summer", etc.

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 StartDay; // 1, 38, 75, 112

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Duration; // 37 or 39

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWeatherProbability> WeatherChances;

	FWeatherProbability GetRandomWeather() const;
};

/**
 *
 */
UCLASS()
class DYNAMICWEATHER_API USeasonWeatherDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	// UPROPERTY(EditAnywhere, Category = SeasonWeather)
	// int32 TotalDaysInYear;

	UPROPERTY(EditAnywhere, Category = "SeasonWeatherInfo")
	TArray<FSeasonWeatherInfo> SeasonWeatherInfos;
};
