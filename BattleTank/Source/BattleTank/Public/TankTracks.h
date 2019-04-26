// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 TankTracks is used for setting up maximum driving force, and apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))//, HideCategories = "Collision")
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Set throttle between -1.0 and 1.0
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
};
