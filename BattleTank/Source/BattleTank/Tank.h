// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintPure, Category="Health")
	float getHealthPercentage() const;

	FTankDelegate onDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32  startingHealth = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32  currentHealth = startingHealth;
};
