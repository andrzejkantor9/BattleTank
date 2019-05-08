// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"


UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//calculate the slippage speed
	FVector TankRightVector = GetRightVector();
	FVector ComponentSpeed = GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(TankRightVector, ComponentSpeed);

	//work-out required acceleration this frame to correct
	auto CorrectionOfAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculated and apply sideways force (F = m * A)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionOfForce = (TankRoot->GetMass() * CorrectionOfAcceleration) / 2; //dividing by 2 because there are two tracks
	TankRoot->AddForce(CorrectionOfForce);
}

void UTankTracks::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}