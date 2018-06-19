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

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto Time = GetWorld()->GetTimeSeconds();
	if (AmmoCount == 0)
	{
		FiringStatus = EFiringState::NoAmmo; //TODO Set Color in BP and Reload Function
		if ((Time - LastFireTime) > ReloadTimeInSeconds && FiringStatus == EFiringState::NoAmmo) Reload();
	}
	else if (AmmoCount > 0) {
		if ((Time - LastFireTime) < FireTimeInSeconds)
		{
			FiringStatus = EFiringState::Reloading;
		}
		else if (BarrelMoving)
		{
			FiringStatus = EFiringState::Aiming;
		}
		else FiringStatus = EFiringState::Locked; 
	}
}

void UTankAimingComponent::BeginPlay()
{
	auto Time = GetWorld()->GetTimeSeconds();
	LastFireTime = Time;
}

bool UTankAimingComponent::IsBarrelMoving(FVector AimDirection) {

	if (!ensure(Barrel)) return false;
	auto BarrelRotator = Barrel->GetForwardVector();
	if (AimDirection.Equals(BarrelRotator, .01)) return false;
	return true;
}
void UTankAimingComponent::InitializeAimingComponents(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) return;
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel && Turret)) return;
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

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;
	// Figure the distance between current barrel rotation and Aim Direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	if (DeltaRotator.Yaw < 180) Turret->Rotate(DeltaRotator.Yaw);
	else Turret->Rotate(FMath::Abs<float>(DeltaRotator.Yaw));
	BarrelMoving = IsBarrelMoving(AimDirection);
}

void UTankAimingComponent::Fire() {
	auto Time = GetWorld()->GetTimeSeconds();
	if (!ensure(Barrel && ProjectileBluePrint)) return;
	if( FiringStatus != EFiringState::Reloading && FiringStatus != EFiringState::NoAmmo && AmmoCount > 0)
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
		AmmoCount--;
		//if (AmmoCount == 0) FiringStatus = EFiringState::NoAmmo;
		//else FiringStatus = EFiringState::Reloading;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

void UTankAimingComponent::Reload() {
	UE_LOG(LogTemp, Warning, TEXT("%s: Reloaded."), *GetOwner()->GetName());
	AmmoCount = MaxAmmo;
	//FiringStatus = EFiringState::Aiming;
}

int32 UTankAimingComponent::GetAmmoCount() const {
	return AmmoCount;
}