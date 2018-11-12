// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.f, 1.f);
	auto rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0 , rawNewRotation, 0));


}
