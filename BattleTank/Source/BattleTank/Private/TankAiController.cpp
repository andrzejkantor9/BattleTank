// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAiController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	/*
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI failed to posses a tank."));
		return nullptr;
	}
	FString *controlledTankNamePtr = nullptr;
	FString controlledTankName = controlledTank->GetName();
	controlledTankNamePtr = &controlledTankName;

	if (!playerController)
	{
		UE_LOG(LogTemp, Error, TEXT("%s AI failed to locate the player."), controlledTankNamePtr);
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s AI has located the player %s."), controlledTankNamePtr, playerController);
	}
	*/

	return Cast<ATank>(PlayerPawn);
}

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI failed to posses a tank."));
	}

	GetPlayerTank();
}