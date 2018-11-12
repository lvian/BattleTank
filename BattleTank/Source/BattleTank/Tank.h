// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimComponent* tankAimComponent = nullptr;

public:	
	// Called every frame

	// Called to bind functionality to input

	void aimAt(FVector hitLocation);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void fire();
	
	
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	float projectileSpeed = 10000;
	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile>  projectileBlueprint;

	UTankBarrel* barrel = nullptr;
	double lastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;
	
};
