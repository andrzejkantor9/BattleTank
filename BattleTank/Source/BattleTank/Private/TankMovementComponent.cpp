// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

#include "TankTracks.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Forward Throw: %f."), Throw);

	LeftTrack->SetThrottle(Throw, 2.3f, 1.f);//TODO decrease force when moving in straight line
	RightTrack->SetThrottle(Throw, 2.3f, 1.f);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Right Throw: %f."), Throw);

	//RightThrow = Throw;	
	LeftTrack->SetThrottle(Throw, 2.3f, 2.3f);
	RightTrack->SetThrottle(-Throw, 2.3f, 2.3f);
	
}

void UTankMovementComponent::InitializeComponent(UTankTracks * LeftTrackToSet, UTankTracks * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & OutMoveVelocity, bool bForceMaxSpeed)
{
	//no need to use super, as we're replacing functionality

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = OutMoveVelocity.GetSafeNormal();

	float AIForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(AIForwardThrow);

	float AIRightThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	IntendTurnRight(AIRightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("Forward Throw: %f, Right Throw: %f."), ForwardThrow, RightThrow);
}
