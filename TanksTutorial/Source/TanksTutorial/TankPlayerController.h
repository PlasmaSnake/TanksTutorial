// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class TANKSTUTORIAL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	void AimAtCrosshair();

	// Ray Cast through the Crosshair Dot
	// TRUE if hits anything in the world + returns the out parameter to determine location
	// FALSE if it does not hit anything in the world.
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;



protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompReference);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationX = .5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationY = .33333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
