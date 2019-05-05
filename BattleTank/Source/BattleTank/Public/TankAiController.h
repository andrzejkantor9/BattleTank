// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aiming") //TODO change firing categories to aiming
		UTankAimingComponent *TankAimingComponent = nullptr;

private:
	//How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 3000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.f; //find sensible default

};
