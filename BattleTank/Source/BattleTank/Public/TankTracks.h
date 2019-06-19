// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

class ASprungWheel;

/**
 TankTracks is used for setting up maximum driving force, and apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Set throttle between -1.0 and 1.0
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle, float Multiplier, float ClampForward);

	UTankTracks();

	void SetTurnMultiplier(float Multiplier);

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000000.f; //assume 40 tonne tank, and 1g acceleration //tweaked after this comment

private:

	void DriveTrack(float CurrentThrottle);
	float TurnMultiplier = 2.3f;

	TArray<class ASprungWheel*> GetWheels() const;
};
