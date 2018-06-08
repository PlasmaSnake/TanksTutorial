// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */

UCLASS(meta = (BluePrintSpawnableComponent), hidecategories = ("Collision"))
class TANKSTUTORIAL_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	
	void Rotate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere)
		float MaxRotationSpeed = 30;


};
