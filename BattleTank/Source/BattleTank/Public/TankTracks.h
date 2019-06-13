// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

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

	virtual void BeginPlay() override;

	void ApplySidewaysForce();
	void SetTurnMultiplier(float Multiplier);

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000000.f; //assume 40 tonne tank, and 1g acceleration //tweaked after this comment

private:
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& OutHit);

	void DriveTrack();
	float TurnMultiplier = 2.3f;
	float CurrentThrottle = 0.f;
};
