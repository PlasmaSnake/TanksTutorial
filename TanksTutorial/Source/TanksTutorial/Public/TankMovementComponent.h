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

	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitializeComponent(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);
	
private:
	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;
};
