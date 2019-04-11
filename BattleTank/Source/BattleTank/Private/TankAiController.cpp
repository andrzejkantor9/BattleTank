// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

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

void ATankAiController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation = FVector(.0f); //out parameter
	if (GetSightRayHitLocation(HitLocation)) //has "side effect "- it is going to raytrace
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		//GetWordLocation of linetraced through cursor
		//If it hits the landscape
			//tell the controlled tank to aim at this point
	}
}

//out parameters can be changed in const methods
bool ATankAiController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//raycast through the crosshair untill we hit terrain or limited by range of 9km
	//get the object we hit or information thet we didnt hit anything
	//if we hit the terrain
		//set outhitlocation at point where ray is hitting 
		//return true

	OutHitLocation = FVector(1.f);
	return false;
}