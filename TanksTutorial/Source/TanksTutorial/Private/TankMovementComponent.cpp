// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTracks.h"
#include "TanksTutorial.h"


void UTankMovementComponent::InitializeMovementComponents(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO Double-Speed due to dual input use

}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
	// TODO Double-Speed due to dual input use

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow.Z);
	
}