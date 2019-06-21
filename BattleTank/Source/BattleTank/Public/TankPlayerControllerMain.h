// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerControllerMain.generated.h"

class UTankAimingComponent;
class ATank;

/**
*Responsible for helping the player aim.
**/
UCLASS()
class BATTLETANK_API ATankPlayerControllerMain : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void SetPawn(APawn * InPawn);
	UFUNCTION()
		void OnPossesedTankDeath();
	virtual void Tick(float) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef); //BlueprintImplementableEvent does not need implementation to compile 

	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
		UTankAimingComponent *TankAimingComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = .5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = .33333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.f; //find sensible default

	FVector2D ScreenLocation;
	//start the tank aiming the barrel towards crosshair so that a shoot would hit
	//where the corsshair intersects the world
	void AimTowardsCrosshair();
	bool bGotSightRayHitLocation(FVector &) const;
	bool bGotLookDirection(FVector2D, FVector&) const;
	bool bGotLookVectorHitLocation(FVector, FVector&) const;
	ATank* PossesedTank;
};
