// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::InitializeAimingComponents(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) return;
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!Barrel) return;
	if (!Turret) return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunch Velocity (SuggestProjectileVelocity)
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
		if (bHaveAimSolution)
		{
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}
	}



/*
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	
}
*/
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) return;
	// Figure the distance between current barrel rotation and Aim Direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
}

void UTankAimingComponent::Fire() {
	auto Time = GetWorld()->GetTimeSeconds();
	bool isReloaded = (Time - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		// Find Socket Location on Barrel for Projectile
		auto FiringLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto FiringRotation = Barrel->GetSocketRotation(FName("Projectile"));
		// Spawn Projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			FiringLocation,
			FiringRotation
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = Time;
	}
}