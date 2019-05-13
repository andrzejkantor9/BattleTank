// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/TankPlayerControllerMain.h"
#include "BattleTank.h"

#include "TankAimingComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

void ATankPlayerControllerMain::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }
	FoundAimingComponent(TankAimingComponent);
}

void ATankPlayerControllerMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerControllerMain::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } //e.g. if not possesing
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }

	FVector HitLocation; //out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	UE_LOG(LogTemp, Warning, TEXT("bHasHitLocation: %i"), bGotHitLocation)
	if (bGotHitLocation) //has "side effect "- it is going to raytrace
	{
		TankAimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
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