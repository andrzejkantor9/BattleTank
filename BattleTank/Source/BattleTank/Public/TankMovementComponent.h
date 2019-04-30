// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;

/**
 Responsible for driving the tank from tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void IntendTurnRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitializeComponent(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

	//TODO check best class space
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;
};
