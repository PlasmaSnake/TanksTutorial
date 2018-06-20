// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Aiming,
	Reloading,
	Locked,
	NoAmmo
};

//Holds Projectile information
class AProjectile;
//Holds Tank Barrel Properties and Rotate method
class UTankBarrel;
//Holds Tank Turret Properties and Elevate method
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKSTUTORIAL_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeAimingComponents(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	void Reload();

	EFiringState GetFiringState() const;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	float ElevationSpeed = 1;
	float TurretRotationSpeed = 1;

	bool IsBarrelMoving(FVector AimDirection);
	bool BarrelMoving = false;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float FireTimeInSeconds = 3;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 MaxAmmo = 4;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetAmmoCount() const;

	int32 AmmoCount = MaxAmmo;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringStatus = EFiringState::Reloading;

	
};
