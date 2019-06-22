// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Windows/WindowsPlatformMath.h"

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
void ATank::SetAiHealth()
{
	StartingHealth = AIHealth;
	CurrentHealth = AIHealth;
}
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("ATank BeginPlay()"));

	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
	AActor * DamageCauser
)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}