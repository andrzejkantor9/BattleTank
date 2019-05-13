// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

#include "TankTracks.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
		
	LeftTrack->SetThrottle(Throw, 1.f, 0.33f);//TODO decrease force when moving in straight line
	RightTrack->SetThrottle(Throw, 1.f, .33f);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	RightThrow = Throw;	
	LeftTrack->SetThrottle(Throw, 2.3f, 1.f );
	RightTrack->SetThrottle(-Throw, 2.3f, 1.f);
	
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

	float AIForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(AIForwardThrow);

	float AIRightThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	IntendTurnRight(AIRightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("Forward Throw: %f, Right Throw: %f."), ForwardThrow, RightThrow);
}
