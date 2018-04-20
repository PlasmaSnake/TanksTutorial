// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "TanksTutorial.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//auto ControlledTank = GetControlledTank();
	//if (!ControlledTank){ UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is not possessing a tank.")); }
	//else UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Begin Play on %s"), *(GetControlledTank()->GetName()));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



