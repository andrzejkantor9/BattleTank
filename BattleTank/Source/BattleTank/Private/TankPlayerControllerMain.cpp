// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "../public/TankPlayerControllerMain.h"

ATank* ATankPlayerControllerMain::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}