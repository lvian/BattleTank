// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Input)
	void setThrottle(float throttle);

	void DriveTrack(float currentThrotle);

	UPROPERTY(EditDefaultsOnly)
	float drivingForce = 400000;
private:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels();
};
