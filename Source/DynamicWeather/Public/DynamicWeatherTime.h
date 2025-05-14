// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DynamicWeatherTime.generated.h"

USTRUCT()
struct FDynamicWeatherTime
{
	GENERATED_BODY()

public:
	static constexpr float SecondsPerHour = 3600.f;
    static constexpr float SecondsPerMinute = 60.f;

public:
	FDynamicWeatherTime(int32 InHours = 0, int32 InMinutes = 0, int32 InSeconds = 0);
	
	bool operator==(const FDynamicWeatherTime& RHS) const;
    bool operator!=(const FDynamicWeatherTime& RHS) const;
    
    float ToHours() const;
    float ToSeconds() const;
    
    static FDynamicWeatherTime FromHours(float InHours);
    static FDynamicWeatherTime FromSeconds(float InSeconds);
	
	FString ToString(bool bForceSignDisplay = false) const
	{
		const bool bHasNegativeComponent = Hours < 0 || Minutes < 0 || Seconds < 0;
		const TCHAR* SignText = bHasNegativeComponent ? TEXT("- ") : bForceSignDisplay ? TEXT("+ ") : TEXT("");
		
        TStringBuilder<34> Builder;
        Builder.Appendf(TEXT("%s%02d:%02d:%02d"), SignText, FMath::Abs(Hours), FMath::Abs(Minutes), FMath::Abs(Seconds));
        	
        return Builder.ToString();
	}
	
public:
	
	UPROPERTY()
	int32 Hours;

	UPROPERTY()
	int32 Minutes;

	UPROPERTY()
	int32 Seconds;
};
