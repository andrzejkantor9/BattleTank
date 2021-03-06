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
	Locked,
	OutOfAmmo
};

class UTankBarrel;
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
		bool bCanTankFire();

	void AimAt(FVector HitLocation);
	EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = "Aiming")
		int32 GetRoundsLeft() const;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
		EFiringState FiringState = EFiringState::Reloading;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector TargetAimDirection);
	void RotateTurret(FVector TargetAimDirection);
	bool bIsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000.f; //find sensible default
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 RoundsLeft = 20;

	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	double LastFireTime = 0.f;
	FVector AimDirection;
};
