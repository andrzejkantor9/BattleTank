// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h" // generated.h always must be last include

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector HitLocation);

protected:
	UTankAimingComponent *TankAimingComponent = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* ) override;
};
