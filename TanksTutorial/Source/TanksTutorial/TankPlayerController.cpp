// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TanksTutorial.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) return;
	FoundAimingComponent(TankAimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(GetPawn()) || !ensure(TankAimingComponent)) return;

	FVector HitLocation; // OUT Parameter
	if (GetSightRayHitLocation(HitLocation)) {
		TankAimingComponent->AimAt(HitLocation);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Look Error"));
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const{
	// Find Crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairLocationX, ViewportSizeY*CrossHairLocationY);

	// Look for direction of aim relative to world
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-Trace Along LookDirection and see what we hit.
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
	}
	return false;
} // contains out parameter for HitLocation


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldHitLocation;  // Not used
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldHitLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto PlayerLocation = PlayerCameraManager->GetCameraLocation();
	auto LineTraceEnd = PlayerLocation + LookDirection * LineTraceRange;
	FCollisionQueryParams traceParameters(FName(TEXT("")), true, this);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PlayerLocation,
		LineTraceEnd,
		ECollisionChannel::ECC_Visibility,
		traceParameters
	)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
