// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicWeatherTime.h"
#include "ProceduralDayTimer.h"
#include "SeasonWeatherData.h"
#include "GameFramework/Actor.h"
#include "InstancedStruct.h"
#include "BaseDayActor.generated.h"

class UDayTimer;
class USeasonWeatherDataAsset;
class UDayTimerCollectionAsset;
class USkyAtmosphereComponent;
class USkyLightComponent;
class UVolumetricCloudComponent;
class UDirectionalLightComponent;
class UExponentialHeightFogComponent;
class UStaticMeshComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS(Blueprintable)
class DYNAMICWEATHER_API ABaseDayActor : public AActor
{
	GENERATED_BODY()

public:

	ABaseDayActor(const FObjectInitializer& Init);

public:

	UDayTimer* GetCurrentDayTimer() const;

	/**
     * Get the duration of each day cycle in hours (assuming PlayRate is 1.0)
     *
     * @return float, time in Seconds
     */
	UFUNCTION(BlueprintCallable, Category="TimeOfDay")
	float GetTimePerCycleToSeconds() const;

	/**
	 * Get the duration of each DayLength in hours (assuming PlayRate is 1.0)
	 *
	 * @return float, DayLength in Seconds
	 */
	UFUNCTION(BlueprintCallable, Category="TimeOfDay")
	float GetDayLengthToSeconds() const;

	/**
    * Get the duration of each InitialTimeOfDay in hours (assuming PlayRate is 1.0)
    *
    * @return float, InitialTimeOfDay in Seconds
    */
	UFUNCTION(BlueprintCallable, Category="TimeOfDay")
	float GetInitialTimeOfDayToSeconds() const;

	/**
	* Get the duration of each InitialTimeOfDay in hours (assuming PlayRate is 1.0)
	*
	* @return float, InitialTimeOfDay in Hours
	*/
	UFUNCTION(BlueprintCallable, Category="TimeOfDay")
	float GetInitialTimeOfDayToHour() const;

	void SetCurrentTimeFromSeconds(float Seconds);

	UFUNCTION()
	void SetCurrentTimeFromHours(float Hours);
    void NormalizeTime();

	void AdvanceDay();
    UFUNCTION(BlueprintCallable)
	void AdvanceTime(int32 InHours);
    UFUNCTION(CallInEditor)
    void TestAdvanceTime();
    void NextDay();

    UFUNCTION(BlueprintCallable, CallInEditor)
    void JumpToNextDay();

    bool IsAfterMidnight() const;
protected:

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:

	virtual void InitializeDayTimers();
	UFUNCTION()
	virtual void InitializeSeasonWeatherTimer();

	UFUNCTION()
	virtual void StartCurrentTimer();
	virtual void InitializeCurrentSeasonWeather();

public:
	EWeatherType GetWeatherType() const {return CurrentWeatherType;};
	bool IsRaining() const;

protected:

	/** Standard Components **/

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SunRootComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDirectionalLightComponent> SunComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkyAtmosphereComponent> SkyAtmosphereComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkyLightComponent> SkyLightComponent;

	/** Optional Components **/

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFogComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVolumetricCloudComponent> VolumetricCloudComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SkySphereComponent;

protected:

#if WITH_EDITORONLY_DATA

	/** 편집기에서 미리 보기할 시간을 설정합니다. 런타임 시 시작 시간에는 영향을 미치지 않습니다.*/
	UPROPERTY(EditAnywhere, Category = Preview, NonTransactional)
	FDynamicWeatherTime TimeOfDayPreview;
#endif

	/** 하루 주기의 전체 길이 (지속 시간) */
	UPROPERTY(EditAnywhere, Category = RuntimeDayCycle)
	FDynamicWeatherTime DayLength;

	/** 월드 시간 상에서 하루 주기를 완료하는 데 걸리는 시간
	 이 값이 DayLength와 같다면 실제 세계 시간(real-time)을 사용한다는 의미입니다 */
	UPROPERTY(EditAnywhere, Category = RuntimeDayCycle)
	FDynamicWeatherTime TimePerCycle;

	/** 하루 주기가 시작되는 초기 시간 */
	UPROPERTY(EditAnywhere, Category = RuntimeDayCycle)
	FDynamicWeatherTime InitialTimeOfDay;

	/** 계절을 갖고 있는지 */
	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	bool bHasSeason;

	/** 현재 시간 */
	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	FDynamicWeatherTime CurrentTime;

	/** 1년 총 일수 */
	UPROPERTY(VisibleAnywhere, Category = SeasonWeather)
	int32 TotalDaysInYear;

	/** 현재 일수 */
	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	int32 CurrentDayOfYear =1;

	/** 게임 내 진행 중인 "해당 해" */
	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	int32 CurrentYear;

	/** 현재 계절 */
	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	FString CurrentSeason;

	/** 현재 날씨 타입 */
	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	EWeatherType CurrentWeatherType;

	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	TObjectPtr<UDayTimer> CurrentTimer;

	UPROPERTY(EditAnywhere, Category = SeasonWeather)
	TArray<TInstancedStruct<FProceduralDayTimer>> ProceduralDayTimers;

	TArray<TInstancedStruct<FProceduralDayTimer>> PreProceduralDayTimers;

	UPROPERTY()
	TArray<TWeakObjectPtr<UNiagaraComponent>> NiagaraComponentPool;

private:
	void ActivateNiagaraForTimers(const TArray<TInstancedStruct<FProceduralDayTimer>>& Timers);
	void DeactivateNiagaraForTimers(const TArray<TInstancedStruct<FProceduralDayTimer>>& Timers);
	UNiagaraComponent* FindOrAddNiagaraComponent(UNiagaraSystem* NiagaraSystem);

public:

	UPROPERTY(EditAnywhere, Category="Timer")
	TArray<TObjectPtr<UDayTimerCollectionAsset>> DaySequenceCollections; // 계절이 없는 단순 하루

	UPROPERTY(EditAnywhere, Category="Timer")
	TObjectPtr<USeasonWeatherDataAsset> SeasonWeatherDataAsset; // 사계절이 존재하는 데이터
};
