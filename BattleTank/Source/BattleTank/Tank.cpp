// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::getHealthPercentage() const
{

	return (float) currentHealth / (float)startingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = startingHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(Damage);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, currentHealth);

	currentHealth -= damageToApply;
	if (currentHealth <= 0 )
	{
		onDeath.Broadcast();
	}
	UE_LOG(LogClass, Warning, TEXT("HIT"));
	return damageToApply;
}


// Called to bind functionality to input


