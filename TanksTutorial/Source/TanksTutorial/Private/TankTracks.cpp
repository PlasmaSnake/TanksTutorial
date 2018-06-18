// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "Engine/World.h"

void UTankTracks::SetThrottle(float Throttle)
{

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) return;
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


