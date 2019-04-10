// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI is possesing: %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI failed to posses a tank."));
	}
}