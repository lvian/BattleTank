// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAimComponent.h"
#include "AiTankController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API AAiTankController : public AAIController
{
	GENERATED_BODY()
	
	
public:

	APawn* playerTank = nullptr ;
	APawn* controlledTank = nullptr;
	void BeginPlay() override;
	void Tick(float deltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	float acceptanceRadius = 8000;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void onPossessedTankDeath();
	
};
