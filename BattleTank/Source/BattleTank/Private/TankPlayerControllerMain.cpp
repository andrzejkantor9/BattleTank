// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/TankPlayerControllerMain.h"
#include "BattleTank.h"

#include "Tank.h"
#include "TankAimingComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

void ATankPlayerControllerMain::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller cannot find Aiming Component"))
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
	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation; //out parameter
	if (GetSightRayHitLocation(HitLocation)) //has "side effect "- it is going to raytrace
	{
		GetControlledTank()->AimAt(HitLocation);
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
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
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

bool ATankPlayerControllerMain::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation(); 
	FVector LineTraceEnd = LineTraceStart + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult, 
			LineTraceStart, 
			LineTraceEnd, 
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		//DrawDebugLine(GetWorld(), LineTraceStart, HitLocation, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}
