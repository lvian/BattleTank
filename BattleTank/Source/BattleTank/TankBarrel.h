// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditAnywhere)
	float maxDegreesPerSecond = 20;
	
	UPROPERTY(EditAnywhere)
	float maxElevation = 40;
	
	UPROPERTY(EditAnywhere)
	float minElevation = 0;

};
