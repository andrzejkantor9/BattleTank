// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

#include "TankTracks.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetTurnMultiplier(1.f);
	RightTrack->SetTurnMultiplier(1.f);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	
	//float TurnMultiplier = 1.5f; //TODO enable turning in place
	/*if (GetOwner()->GetVelocity().X == 0.f 
		&&
		GetOwner()->GetVelocity().Y == 0.f
		) { TurnMultiplier = 2.5f; }*/

	LeftTrack->SetTurnMultiplier(1.f);
	RightTrack->SetTurnMultiplier(1.f);
	LeftTrack->SetThrottle(Throw );
	RightTrack->SetThrottle(-Throw);
	
}

void UTankMovementComponent::InitializeComponent(UTankTracks * LeftTrackToSet, UTankTracks * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//no need to use super, as we're replacing functionality

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	IntendTurnRight(RightThrow);
	
//	UE_LOG(LogTemp, Warning, TEXT("Forward Throw: %f, Right Throw: %f."), ForwardThrow, RightThrow);
}
