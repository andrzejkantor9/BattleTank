// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../public/TankPlayerControllerMain.h"

ATank* ATankPlayerControllerMain::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerControllerMain::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is possesing: %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player failed to posses a tank."));
	}
}