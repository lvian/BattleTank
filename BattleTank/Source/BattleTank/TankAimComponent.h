// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"


UENUM()
enum class EFiringStatus : uint8
{
	locked,
	aimming,
	reloading
};




class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingStatus = EFiringStatus::reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void aimAt(FVector aimAtLocation, float projectileSpeed);
	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialize(UTankBarrel* barrelRef, UTankTurret* turretRef);
	
	void moveBarrelTowards(FVector aimDirection);
	void moveTurretTowards(FVector aimDirection);

private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	

};
