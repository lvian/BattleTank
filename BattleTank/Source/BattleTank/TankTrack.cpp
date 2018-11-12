// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::setThrottle(float throttle)
{
	auto forceApplied = GetForwardVector() * throttle * drivingForce;
	auto forceLocation = GetComponentLocation();
	auto rootComponent = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent() );

	rootComponent->AddForceAtLocation(forceApplied, forceLocation);

}
