// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerControllerMain.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerControllerMain : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

private:
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = .5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = .33333f;
	FVector2D ScreenLocation;

	ATank* GetControlledTank() const;
	//start the tank aiming the barrel towards crosshair so that a shoot would hit
	//where the corsshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
};
