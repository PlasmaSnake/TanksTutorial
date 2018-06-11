// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankTracks.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

//void ATank::SetTracksReference(UTankTracks* TracksToSet)
//{
	//TODO Implement TankMovingComponent
//}

void ATank::Fire(){
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

