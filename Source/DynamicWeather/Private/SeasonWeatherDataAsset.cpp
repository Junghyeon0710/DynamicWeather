// Fill out your copyright notice in the Description page of Project Settings.


#include "SeasonWeatherDataAsset.h"

FWeatherProbability FSeasonWeatherInfo::GetRandomWeather() const
{
	float TotalWeight = 0.0f;
	for (const FWeatherProbability& Chance : WeatherChances)
	{
		TotalWeight += Chance.Probability;
	}

	if (TotalWeight <= 0.0f || WeatherChances.IsEmpty())
	{
		// fallback: 그냥 첫 번째를 리턴하거나 디폴트 생성
		return FWeatherProbability{};
	}

	const float RandomValue = FMath::FRandRange(0.0f, TotalWeight);
	float Accumulated = 0.0f;

	for (const FWeatherProbability& Chance : WeatherChances)
	{
		Accumulated += Chance.Probability;
		if (RandomValue <= Accumulated)
		{
			return Chance;
		}
	}

	// 만약 무언가 잘못되었을 경우
	return WeatherChances.Last();
}
