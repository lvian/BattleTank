// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent( DeltaTime,  TickType,  ThisTickFunction);

	
}

void UTankTrack::setThrottle(float throttle)
{
	float localThrotle = FMath::Clamp<float>( throttle, -1, 1);
	DriveTrack(localThrotle);
}

void UTankTrack::DriveTrack(float currentThrotle)
{
	auto forceApplied = currentThrotle * drivingForce;
	
	auto Wheels = GetWheels();
	auto forcePerWheel = forceApplied / Wheels.Num();
	for (ASprungWheel* wheel : Wheels)
	{
		wheel->addDrivingForce(forcePerWheel);

	}
}


TArray<class ASprungWheel*> UTankTrack::GetWheels()
{
	TArray<ASprungWheel*> resultArray;
	TArray<USceneComponent*> children;
	GetChildrenComponents(true, children);

	for (USceneComponent* child : children) {
		auto spawnPointChild = Cast<USpawnPoint>(child);
		if (!spawnPointChild) continue;

		AActor* spawnedChild = spawnPointChild->getSpawnedActor();
		auto sprungWheel = Cast<ASprungWheel>(spawnedChild);
		if (!sprungWheel) continue;

		resultArray.Add(sprungWheel);

	}


	return resultArray;
}

