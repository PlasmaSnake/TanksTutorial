// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for driving tracks
 */

class UTankTracks;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKSTUTORIAL_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeMovementComponents(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throw);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;
};
