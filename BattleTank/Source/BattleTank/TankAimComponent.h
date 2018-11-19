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
	reloading,
	outOfAmmo
};



class AProjectile;
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

	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile>  projectileBlueprint;

	

public:	
	// Called every frame
	bool isBarrelMoving();
	void aimAt(FVector aimAtLocation);
	
	EFiringStatus getFiringStatus();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialize(UTankBarrel* barrelRef, UTankTurret* turretRef);
	
	void moveBarrelTowards(FVector aimDirection);
	void moveTurretTowards(FVector aimDirection);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void fire();

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
		int32 ammunition = 25;


private:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	FVector aimDirection{0};

	UPROPERTY(EditAnywhere, Category = "Firing")
	float projectileSpeed = 10000;

	double lastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	

};
