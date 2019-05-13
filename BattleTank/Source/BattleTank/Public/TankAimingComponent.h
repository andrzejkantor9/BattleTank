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
class AProjectile;

//Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeComponent(UTankBarrel* BarrelToSet, UTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Aiming")
		void Fire();

	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
		EFiringState FiringState = EFiringState::Reloading;
private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector AimDirection);
	void RotateTurret(FVector AimDirection);
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 20000.f; //find sensible default
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.f;
	
	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	double LastFireTime = 0.f;
	FVector AimDirection;
};
