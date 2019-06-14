// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

#include "TankAimingComponent.h"
#include "Tank.h" //So we can implement OnDeath

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

	APawn* PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	APawn* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);//TODO find out if the unit is in cm

	//aim towards player
	UTankAimingComponent* TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	//if aiming or locked then fire
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		TankAimingComponent->Fire();
	}
}

void ATankAiController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank has recieved OnDeath BroadCast!"));

	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAiController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossesedTank = Cast<ATank>(InPawn);
		if (!PossesedTank) { return; }

		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnPossesedTankDeath );
		//TODO Subscribe our local method to the tank's death event
	}
}
