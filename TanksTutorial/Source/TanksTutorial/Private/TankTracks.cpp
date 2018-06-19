// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "Engine/World.h"

UTankTracks::UTankTracks() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::BeginPlay()
{

	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
	DriveTracks();
	ApplySidewaysForce();
	CurrentThrottle = 0;
	//UE_LOG(LogTemp, Warning, TEXT("%s: %s is touching the ground"), *GetOwner()->GetName() , *HitComponent->GetName());
}

void UTankTracks::SetThrottle(float Throttle)
{

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTracks::ApplySidewaysForce() {
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	if (!ensure(TankRoot)) return;
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work out the required accel this frame to correct 
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways friction (F = m a)
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::DriveTracks()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) return;
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}