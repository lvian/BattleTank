// Fill out your copyright notice in the Description page of Project Settings.

#include "AiTankController.h"
#include "Tank.h"
#include "TankAimComponent.h"


void AAiTankController::BeginPlay()
{
	Super::BeginPlay();
	
	controlledTank = GetPawn();

	if (controlledTank)
	{
		UE_LOG(LogClass, Warning, TEXT("Ai Tank: %s"), *controlledTank->GetName());
	}


	playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (playerTank)
	{
		UE_LOG(LogClass, Warning, TEXT("Player Tank: %s"), *playerTank->GetName());
	}


}

void AAiTankController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (!ensure(playerTank && controlledTank)) {return;}

	auto result = MoveToActor(playerTank, acceptanceRadius, true, true, false, 0, true);
		
	auto aimComponent = controlledTank->FindComponentByClass<UTankAimComponent>();

	aimComponent->aimAt(playerTank->GetActorLocation());
	if (aimComponent->getFiringStatus() == EFiringStatus::locked)
	{
		aimComponent->fire();
	}
	
}

void AAiTankController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank) ){return;}

		possessedTank->onDeath.AddUniqueDynamic(this, &AAiTankController::onPossessedTankDeath);
	}
}

void AAiTankController::onPossessedTankDeath()
{
	UE_LOG(LogClass, Warning, TEXT("AI DEAD"));

	controlledTank->DetachFromControllerPendingDestroy();
}