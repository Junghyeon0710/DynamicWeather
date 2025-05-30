#pragma once

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	Sunny      UMETA(DisplayName = "맑음"),
	Rain       UMETA(DisplayName = "비"),
	HeavyRain  UMETA(DisplayName = "폭우"),
	Cloudy     UMETA(DisplayName = "흐림"),
	Snow       UMETA(DisplayName = "눈")
};