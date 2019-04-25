// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}
void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>
		(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>
		(GetPawn());

	if (PlayerTank)
	{
		//TODO move towards player

		//aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire(); //TODO limit fire rate
	}
}
/*
ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}*/
/*
ATank * ATankAiController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}*/