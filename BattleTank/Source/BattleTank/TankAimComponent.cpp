// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	// ...
	
}


// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimComponent::aimAt(FVector aimAtLocation, float projectileSpeed)
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
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		moveBarrelTowards(aimDirection);
		moveTurretTowards(aimDirection);
	}
	
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

	turret->rotate(deltaRotator.Yaw);

	return;
}
