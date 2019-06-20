// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/TankPlayerControllerMain.h"
#include "BattleTank.h"

#include "TankAimingComponent.h"
#include "Tank.h"

#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

void ATankPlayerControllerMain::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerControllerMain::OnPossesedTankDeath);
		//TODO Subscribe our local method to the tank's death event
	}
}

void ATankPlayerControllerMain::OnPossesedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerControllerMain::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn())
	{
		UE_LOG(LogTemp, Error, TEXT("ATankPlayerControllerMain failed to GetPawn() in BeginPlay()."));
		return;
	}
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
	bool bGotHitLocation = bGotSightRayHitLocation(HitLocation);
	if (bGotHitLocation) //has "side effect "- it is going to raytrace
	{
		TankAimingComponent->AimAt(HitLocation);
	}
}

//out parameters can be changed in const methods
bool ATankPlayerControllerMain::bGotSightRayHitLocation(FVector &OutHitLocation) const
{
	//find the crosshair position
	//"de-project" the screen position of the crosshair to a world direction
	//line-trace along that look direction and see what we hit (up to max range)
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D TargetScreenLocation = FVector2D((StaticCast<float>(ViewportSizeX) * CrosshairXLocation), (StaticCast<float>(ViewportSizeY) * CrosshairYLocation));

	FVector LookDirection;
	if (bGotLookDirection(TargetScreenLocation, LookDirection))
	{
		return bGotLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	//raycast through the crosshair untill we hit terrain or limited by range of 9km
	//get the object we hit or information thet we didnt hit anything
	//if we hit the terrain
		//set outhitlocation at point where ray is hitting 
		//return true

	OutHitLocation = FVector(1.f);
	return false;
}

bool ATankPlayerControllerMain::bGotLookDirection(FVector2D TargetScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; //to be disbanded
	return DeprojectScreenPositionToWorld(
		TargetScreenLocation.X, 
		TargetScreenLocation.Y, 
		CameraWorldLocation, 
		OutLookDirection);
}

bool ATankPlayerControllerMain::bGotLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const
{
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation(); 
	FVector LineTraceEnd = LineTraceStart + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult, 
			LineTraceStart, 
			LineTraceEnd, 
			ECollisionChannel::ECC_Camera)
		)
	{
		OutHitLocation = HitResult.Location;
		//DrawDebugLine(GetWorld(), LineTraceStart, HitLocation, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
		return true;
	}
	OutHitLocation = FVector(0.f);
	return false;
}

