// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

#include "TankTracks.h"
#include "Tank.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	if (FMath::Abs(Throw) > TankMovementSFXTriggerThrow)
	{
		ATank *PossesedTank = Cast<ATank>(GetOwner());
		if (PossesedTank)
		{
			//PossesedTank->TankMovingSFX();
		}
		bIsTankMoving = true;
	}
	else
	{
		bIsTankMoving = false;
	}

	LeftTrack->SetThrottle(Throw, 2.3f, 1.f);
	RightTrack->SetThrottle(Throw, 2.3f, 1.f);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

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
}
