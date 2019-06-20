// Copyright info

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent *Wheel= nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent *Axle = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UPhysicsConstraintComponent *MassWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UPhysicsConstraintComponent *AxleWheelConstraint = nullptr;

private:
	void SetupConstraint();
	void ApplyForce();

	float TotalForceMagnitudeThisFrane = 0.f;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
