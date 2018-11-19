// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimComponent::initialize(UTankBarrel* barrelRef, UTankTurret* turretRef)
{
	barrel = barrelRef;
	turret = turretRef;
}


// Called when the game starts
void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();

	lastFireTime = FPlatformTime::Seconds();
	
}



void UTankAimComponent::aimAt(FVector aimAtLocation)
{
	if (!barrel) { return; };

	FVector outLaunchVelocity{ 0 };
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));


	bool bAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		aimAtLocation,
		projectileSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bAimSolution)
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		moveBarrelTowards(aimDirection);
		moveTurretTowards(aimDirection);
	}
	
}

EFiringStatus UTankAimComponent::getFiringStatus()
{
	return firingStatus;
}


void UTankAimComponent::moveBarrelTowards(FVector aimDirection)
{
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - barrelRotator;

	barrel->elevate(deltaRotator.Pitch);

	return;
}

void UTankAimComponent::moveTurretTowards(FVector aimDirection)
{
	auto turretRotator = turret->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - turretRotator;

	if (FMath::Abs( deltaRotator.Yaw) < 180)
	{
		turret->rotate( deltaRotator.Yaw );
	}
	else {
		turret->rotate(-deltaRotator.Yaw);
	}
	

	return;
}



void UTankAimComponent::fire()
{
	if (firingStatus == EFiringStatus::locked || firingStatus == EFiringStatus::aimming)
	{
		if (!ensure(barrel)) { return; }
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->launch(projectileSpeed);
		ammunition--;
		lastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (ammunition == 0)
	{
		firingStatus = EFiringStatus::outOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingStatus = EFiringStatus::reloading;
	}
	else if (isBarrelMoving())
	{
		firingStatus = EFiringStatus::aimming;
	}
	else
	{
		firingStatus = EFiringStatus::locked;
	}
	
}


bool UTankAimComponent::isBarrelMoving()
{
	if (!ensure(barrel)) { return false; }

	return ! barrel->GetForwardVector().Equals(aimDirection, 0.05);
}
