// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimComponent.h"
#include "Tank.h"
#include "BattleTank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetPawn();
	
	auto aimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	foundAimingComponent(aimComponent);
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (!GetPawn()) { return; }
	
	AimTowardsCrosshair();

}


void ATankPlayerController::AimTowardsCrosshair()
{
	auto aimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(aimComponent)) { return; };

	FVector hitLocation;

	auto hitResult = GetSightRayHitLocation(hitLocation);
	if (hitResult)
	{
		aimComponent->aimAt(hitLocation);
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
		return GetLookVectorHitLocation(lookDirection, outHitLocation);
	};

	return false;
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
			ECollisionChannel::ECC_Camera)
		) 
	{
		hitlocation = outHitResult.Location;
		return true;
	}
	
	hitlocation = FVector(0);
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	UE_LOG(LogClass, Warning, TEXT("Call"));
	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		UE_LOG(LogClass, Warning, TEXT("call 2"));
		possessedTank->onDeath.AddUniqueDynamic(this, &ATankPlayerController::onPossessedTankDeath);
	}
}

void ATankPlayerController::onPossessedTankDeath()
{
	UE_LOG(LogClass, Warning, TEXT("Player DEAD"));

	auto controlledTank = GetWorld()->GetFirstPlayerController();

	controlledTank->StartSpectatingOnly();
}