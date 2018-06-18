// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TanksTutorial.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(PlayerTank) && ensure(TankAimingComponent))
	{
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
		// Aim at player
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		TankAimingComponent->Fire();
	}
}