// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // generated.h always must be last include

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
public:
	virtual float TakeDamage
	(
		float DamageAmount, 
		struct FDamageEvent const & DamageEvent, 
		class AController * EventInstigator, 
		AActor * DamageCauser
	) override;
	void SetDead(bool bIsDead);

	//Return current health as a procentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Healt")
		float GetHealthPercent() const;

	FTankDelegate OnDeath;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
		bool bDead = false;

private:
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth; //initialized in BeginPlay
};
