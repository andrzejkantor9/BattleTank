// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

class UTankAimingComponent;
class ATank;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	//How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup") 
		float AcceptanceRadius = 8000.f;
	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
		bool bIsDead = false;

private:
	virtual void SetPawn(APawn *InPawn) override;
	APawn* ControlledTank;
	ATank* PossesedTank;

	UFUNCTION()
		void OnPossesedTankDeath();
};
