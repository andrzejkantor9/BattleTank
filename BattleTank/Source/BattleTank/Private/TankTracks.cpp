// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"

float UTankTracks::TurnMultiplier = 1.f;

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::ApplySidewaysForce()
{
	//work-out required acceleration this frame to correct
	FVector TankRightVector = GetRightVector();
	FVector ComponentSpeed = GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(TankRightVector, ComponentSpeed);

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionOfAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculated and apply sideways force (F = m * A)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionOfForce = (TankRoot->GetMass() * CorrectionOfAcceleration) / 2; //dividing by 2 because there are two tracks
	TankRoot->AddForce(CorrectionOfForce);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ON GROUND HIT"));

	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.f;
}

void UTankTracks::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	CurrentThrottle *= TurnMultiplier;
}

void UTankTracks::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}