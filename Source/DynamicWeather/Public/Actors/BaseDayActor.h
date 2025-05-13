// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "BaseDayActor.generated.h"

class USkyAtmosphereComponent;
class USkyLightComponent;
class UVolumetricCloudComponent;
class UDirectionalLightComponent;
class UExponentialHeightFogComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class DYNAMICWEATHER_API ABaseDayActor : public AInfo
{
	GENERATED_BODY()

public:

	ABaseDayActor(const FObjectInitializer& Init);

protected:

	virtual void BeginPlay() override;

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
};
