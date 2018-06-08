// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TanksTutorial.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//auto ControlledAITank = GetControlledAITank();
	//if (!ControlledAITank) { UE_LOG(LogTemp, Warning, TEXT("This AI Controller is empty")); }
	//else UE_LOG(LogTemp, Warning, TEXT("BeginPlay: AI Controller on %s"), *(GetControlledAITank()->GetName()));

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) { UE_LOG(LogTemp, Warning, TEXT("There is no player tank to be found")); }
	//else UE_LOG(LogTemp, Warning, TEXT("%s targetting %s"), *(GetControlledAITank()->GetName()), *(PlayerTank->GetName()));

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO Move towards player
		
		// Aim at player
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}