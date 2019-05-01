// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // generated.h always must be last include

class UTankAimingComponent;
class UTankBarrel;
class UTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel *BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTurret *TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Actions)
		void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aiming") //TODO change firing categories to aiming
		UTankAimingComponent *TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		UTankMovementComponent *TankMovementComponent = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.f; //find sensible default
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.f;

	//local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	double LastFireTime = 0.f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* ) override;
};
