// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <iostream>
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel; //Forward declaration
class UTurret;

//Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeComponent(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	void MoveBarrelTowards(FVector AimDirection);
	void RotateTurret(FVector AimDirection);

	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
		EFiringState FiringState = EFiringState::Reloading;
private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;
};
