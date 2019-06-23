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

	//Return current health as a procentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Healt")
		float GetHealthPercent() const;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Death")
		void TankDeathExplosion();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Death")
		void RemovePlayerUI();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Death")
		void PlayShootingSFX();
	void SetAiHealth();

	FTankDelegate OnDeath;

private:
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 AIHealth = 40;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth; //initialized in BeginPlay
};
