// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	
	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &outHitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector &lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector &hitlocation) const;


protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void foundAimingComponent(UTankAimComponent* aimCompRef);
private:

	virtual void SetPawn(APawn* InPawn) override;
	
	UFUNCTION()
	void onPossessedTankDeath();

	UPROPERTY(EditAnywhere)
	float crosshairY = 0.3333;

	UPROPERTY(EditAnywhere)
	float crosshairX = 0.5;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;

};


