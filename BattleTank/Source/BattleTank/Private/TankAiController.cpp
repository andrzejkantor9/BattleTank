// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

#include "TankAimingComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("TICK"));

	APawn* PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	APawn* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// move towards player
	UE_LOG(LogTemp, Warning, TEXT("AI tank moving"));
	MoveToActor(PlayerTank, AcceptanceRadius);//TODO find out if the unit is in cm

	//aim towards player
	UTankAimingComponent* TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("FIRING"));
	TankAimingComponent->Fire();
}