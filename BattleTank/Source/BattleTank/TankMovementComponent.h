// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void intendedMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void intendedTurnRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void intendedTurnLeft(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void intendedMoveBackward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialize(UTankTrack * leftTrackToSet, UTankTrack * rightTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;

	

};
