// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))//, HideCategories = "Collision") 
//hide categories - allows to hide categories from edit in blueprint
//that may protect of breaking the game by modyfing unwanted values
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downward speed and +1 upward
	void Elevate(float RelevateSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 10.f; 
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevation= 0.f; 
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevation = 40.f; 
};
