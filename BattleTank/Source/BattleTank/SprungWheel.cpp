// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	physicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(physicsConstraint);

	axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	axle->SetupAttachment(physicsConstraint);
	
	axlePhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxlePhysicsConstraint"));
	axlePhysicsConstraint->SetupAttachment(axle);

	wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	wheel->SetupAttachment(axle);
		
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	wheel->SetNotifyRigidBodyCollision(true);
	wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* bodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!bodyRoot) { return; }
	physicsConstraint->SetConstrainedComponents(bodyRoot, NAME_None, axle, NAME_None);
	axlePhysicsConstraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	forceMagnitudeThisTick = 0;

}

void ASprungWheel::addDrivingForce(float forceMagnitude)
{
	forceMagnitudeThisTick += forceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	wheel->AddForce(axle->GetForwardVector() * forceMagnitudeThisTick);
}
