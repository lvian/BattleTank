// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	tankAimComponent = FindComponentByClass<UTankAimComponent>();
}


// Called to bind functionality to input


void ATank::aimAt(FVector hitLocation)
{
	if (!tankAimComponent) { return; }
	tankAimComponent->aimAt(hitLocation , projectileSpeed);
}

void ATank::fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if (barrel && isReloaded)
	{	
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
		);
		projectile->launch(projectileSpeed);
		
		lastFireTime = FPlatformTime::Seconds();
	}
}
