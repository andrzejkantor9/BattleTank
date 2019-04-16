// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	//move the barrel right amount this frame
	//given max elevation speed, and frame time

	UE_LOG(LogTemp, Warning, TEXT("BarrelElevate() call at speed: %f"), DegreesPerSecond);
}