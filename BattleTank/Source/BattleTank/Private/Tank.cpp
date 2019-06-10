// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Windows/WindowsPlatformMath.h"
float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	//float ToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank died!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount = %f, DamageToApply = %i"), DamageAmount, DamageToApply);

	return DamageToApply;
}