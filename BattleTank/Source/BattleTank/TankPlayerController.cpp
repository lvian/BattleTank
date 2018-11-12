// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimComponent.h"
#include "BattleTank.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	
	auto aimComponent = GetControlledTank()->FindComponentByClass<UTankAimComponent>();

}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardsCrosshair();

}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; };

	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->aimAt(hitLocation);
	};
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * crosshairX, viewportSizeY * crosshairY);

	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		GetLookVectorHitLocation(lookDirection, outHitLocation);
	};

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &lookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector & hitlocation) const
{
	FHitResult outHitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	if ( GetWorld()->LineTraceSingleByChannel(
			outHitResult,
			startLocation,
			endLocation,
			ECollisionChannel::ECC_Visibility)
		) 
	{
		hitlocation = outHitResult.Location;
		return true;
	}
	
	hitlocation = FVector(0);
	return false;
}
