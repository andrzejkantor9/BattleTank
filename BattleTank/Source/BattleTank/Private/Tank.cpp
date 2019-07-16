// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "TankAiController.h"

#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Windows/WindowsPlatformMath.h"
#include "Kismet/KismetSystemLibrary.h"

int32 ATank::AiTankCount = 0;

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
void ATank::SetAiHealth()
{
	StartingHealth = AIHealth;
	CurrentHealth = AIHealth;
}
int32 ATank::BlueprintGetStaticAiTankCount()
{
	NonStaticAiTankCount = AiTankCount;
	return NonStaticAiTankCount;
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
	CurrentHealth = StartingHealth;

	ATankAiController *AiTankController = Cast<ATankAiController>(GetController());
	if (AiTankController) { ++AiTankCount;  }
	NonStaticAiTankCount = AiTankCount;
	//UE_LOG(LogTemp, Warning, TEXT("AiTankCount: %d"), NonStaticAiTankCount);
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