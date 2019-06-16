// Copyright info

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent *Mass= nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent *Wheel= nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UPhysicsConstraintComponent *MassWheelConstraint = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
