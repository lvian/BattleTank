// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	
	auto rightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;

	intendedTurnRight(rightThrow);

	intendedMoveForward(forwardThrow);

}

void UTankMovementComponent::intendedMoveForward(float move)
{
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->setThrottle(move);
	rightTrack->setThrottle(move);
}

void UTankMovementComponent::intendedMoveBackward(float move)
{
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->setThrottle(-move);
	rightTrack->setThrottle(-move);
}

void UTankMovementComponent::intendedTurnLeft(float move)
{
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->setThrottle(-move);
	rightTrack->setThrottle(move);
}

void UTankMovementComponent::intendedTurnRight(float move)
{
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->setThrottle(move);
	rightTrack->setThrottle(-move);
}


