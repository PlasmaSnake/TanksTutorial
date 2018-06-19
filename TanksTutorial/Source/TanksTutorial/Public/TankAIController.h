// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class TANKSTUTORIAL_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	//How close can the AI get to Player Tank
	UPROPERTY(EditAnywhere, Category = "Setup")	
		float AcceptanceRadius = 3000;

	

};
