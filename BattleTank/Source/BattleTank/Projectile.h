// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void destroyProjectile();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void launch(float speed);
	UProjectileMovementComponent* projectileMovement;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(EditAnywhere, Category="Components")
	UParticleSystemComponent* launchBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UParticleSystemComponent* impactBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	URadialForceComponent* explosionForce = nullptr;
	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float destroyDelay = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float projectileDamage = 20;


};


