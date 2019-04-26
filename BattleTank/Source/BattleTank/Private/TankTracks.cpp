// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
	FString Name = GetName(); 
	UE_LOG(LogTemp, Warning, TEXT("At %f projectile is fired at %f speed."), *Name, Throttle);

	//TODO clamp actual throttle value so player can't over-drive
}