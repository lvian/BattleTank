// Fill out your copyright notice in the Description page of Project Settings.

#include "AiTankController.h"
#include "Tank.h"


void AAiTankController::BeginPlay()
{
	Super::BeginPlay();
	
	controlledTank = Cast<ATank>(GetPawn());

	if (controlledTank)
	{
		UE_LOG(LogClass, Warning, TEXT("Ai Tank: %s"), *controlledTank->GetName());
	}


	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (playerTank)
	{
		UE_LOG(LogClass, Warning, TEXT("Player Tank: %s"), *playerTank->GetName());
	}


}

void AAiTankController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (playerTank)
	{
		auto result = MoveToActor(playerTank, 3.f, true, true, false, 0, true);
		
		controlledTank->aimAt(playerTank->GetActorLocation());
		controlledTank->fire();
	}
	
}
