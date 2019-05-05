// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

#include "Tank.h"

#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
//Depends on movement component via pathfinding system

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

	if (ensure(PlayerTank))
	{
		// move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);//TODO find out if the unit is in cm

		//aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire(); //TODO limit fire rate
	}
}
