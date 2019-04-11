// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	virtual void Tick(float ) override;

private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	//start the tank aiming the barrel towards crosshair so that a shoot would hit
	//where the corsshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
};
