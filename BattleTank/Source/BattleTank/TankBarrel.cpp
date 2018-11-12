// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.f, 1.f);
	auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp(rawNewElevation, minElevation, maxElevation);

	SetRelativeRotation(FRotator(elevation, 0, 0));


}
