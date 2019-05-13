// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aiming Component TICK."));
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) 
	{
		FiringState = EFiringState::Reloading; 
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work-out difference between current barrel rotation and desired barrel rotation
	if (!ensure(Barrel)) { return; }
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 
}

void UTankAimingComponent::RotateTurret(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	//always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw )> 180.f)
	{
		Turret->Rotate(DeltaRotator.Yaw * -1.f);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; } // only use ensure if the failure should never happen, otherwise handle the error

	return !(AimDirection.Equals(
		Barrel->GetForwardVector(),
		0.01f));
}

void UTankAimingComponent::InitializeComponent(UTankBarrel * BarrelToSet, UTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity(0.f); 
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, 0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		RotateTurret(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) {	return;	}
	if(!ensure(ProjectileBlueprint)) { return; }


	if (FiringState !=EFiringState::Reloading)
	{
		//spawn the projectile at the socket location at the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}