// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"

#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::SetThrottle(float Throttle, float Multiplier, float ClampForward)
{
	float CurrentThrottle = Multiplier * FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTracks::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceApplied / (Wheels.Num()!=0 ? Wheels.Num() : 1);
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<class ASprungWheel*> UTankTracks::GetWheels() const
{
	TArray<ASprungWheel*> TankWheelsToReturn;
	TArray<USceneComponent*> Children;

	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) { continue; }

		TankWheelsToReturn.Add(SprungWheel);
	}

	return TankWheelsToReturn;
}

void UTankTracks::SetTurnMultiplier(float Multiplier)
{
	TurnMultiplier = Multiplier;
}