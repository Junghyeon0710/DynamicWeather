// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicWeatherTime.h"

FDynamicWeatherTime::FDynamicWeatherTime(int32 InHours, int32 InMinutes, int32 InSeconds)
: Hours(InHours)
, Minutes(InMinutes)
, Seconds(InSeconds)
{}

bool FDynamicWeatherTime::operator==(const FDynamicWeatherTime& RHS) const
{
	return Hours == RHS.Hours && Minutes == RHS.Minutes && Seconds == RHS.Seconds;
}

bool FDynamicWeatherTime::operator!=(const FDynamicWeatherTime& RHS) const
{
	return !operator==(RHS);
}

float FDynamicWeatherTime::ToHours() const
{
	return ToSeconds() / SecondsPerHour;
}

float FDynamicWeatherTime::ToSeconds() const
{
	return Hours * SecondsPerHour + Minutes * SecondsPerMinute + Seconds;
}

FDynamicWeatherTime FDynamicWeatherTime::FromHours(float InHours)
{
	return FromSeconds(InHours * SecondsPerHour);
}

FDynamicWeatherTime FDynamicWeatherTime::FromSeconds(float InSeconds)
{
	float Seconds = InSeconds;
	const float Hours = FMath::Floor(InSeconds / SecondsPerHour);
	Seconds -= Hours * SecondsPerHour;
	const float Minutes = FMath::Floor(Seconds / SecondsPerMinute);
	Seconds -= Minutes * SecondsPerMinute;

	return FDynamicWeatherTime(Hours, Minutes, FMath::Floor(Seconds));
}
