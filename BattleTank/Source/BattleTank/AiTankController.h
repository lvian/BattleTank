// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
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

	ATank* playerTank = nullptr ;
	ATank* controlledTank = nullptr;
	void BeginPlay() override;
	void Tick(float deltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	float acceptanceRadius = 3000;
	
};
