#pragma once

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    None       UMETA(DisplayName = "없음"),      // 날씨 영향 없음 (기본 상태)
	Sunny      UMETA(DisplayName = "맑음"),
	Rain       UMETA(DisplayName = "비"),
	HeavyRain  UMETA(DisplayName = "폭우"),
	Cloudy     UMETA(DisplayName = "흐림"),
	Snow       UMETA(DisplayName = "눈")
};

UENUM(BlueprintType)
enum class EWeekDay : uint8
{
    Monday = 0     UMETA(DisplayName = "월요일"),
    Tuesday     UMETA(DisplayName = "화요일"),
    Wednesday   UMETA(DisplayName = "수요일"),
    Thursday    UMETA(DisplayName = "목요일"),
    Friday      UMETA(DisplayName = "금요일"),
    Saturday    UMETA(DisplayName = "토요일"),
    Sunday      UMETA(DisplayName = "일요일")
};
