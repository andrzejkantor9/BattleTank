// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/TankPlayerControllerMain.h"
#include "BattleTank.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

void ATankPlayerControllerMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerControllerMain::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




void ATankPlayerControllerMain::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation = FVector(.0f); //out parameter
	if (GetSightRayHitLocation(HitLocation)) //has "side effect "- it is going to raytrace
	{
		//GetWordLocation of linetraced through cursor
		//If it hits the landscape
			//tell the controlled tank to aim at this point
	}
}

//out parameters can be changed in const methods
bool ATankPlayerControllerMain::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//find the crosshair position
	//"de-project" the screen position of the crosshair to a world direction
	//line-trace along that look direction and see what we hit (up to max range)
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((StaticCast<float>(ViewportSizeX) * CrosshairXLocation), (StaticCast<float>(ViewportSizeY) * CrosshairYLocation));

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Screen Direction: %s"), *LookDirection.ToString());
	}

	//raycast through the crosshair untill we hit terrain or limited by range of 9km
	//get the object we hit or information thet we didnt hit anything
	//if we hit the terrain
		//set outhitlocation at point where ray is hitting 
		//return true

	OutHitLocation = FVector(1.f);
	return false;
}

bool ATankPlayerControllerMain::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //to be disbanded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}