// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicWeatherTime.h"
#include "GameFramework/Actor.h"
#include "BaseDayActor.generated.h"

class USkyAtmosphereComponent;
class USkyLightComponent;
class UVolumetricCloudComponent;
class UDirectionalLightComponent;
class UExponentialHeightFogComponent;
class UStaticMeshComponent;


UCLASS(Blueprintable)
class DYNAMICWEATHER_API ABaseDayActor : public AActor
{
	GENERATED_BODY()

public:

	ABaseDayActor(const FObjectInitializer& Init);

protected:

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

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
};
