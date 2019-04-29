// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

#include "TankTracks.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward Throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::InitializeComponent(UTankTracks * LeftTrackToSet, UTankTracks * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
