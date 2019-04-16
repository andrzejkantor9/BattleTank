// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), HideCategories = "Collision") 
//hide categories - allows to hide categories from edit in blueprint
//that may protect of breaking the game by modyfing unwanted values
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20.f; 
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation= 0.f; 
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 50.f; 
};
