// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent *CollisionMesh = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		UParticleSystemComponent *LaunchBlast = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		UParticleSystemComponent *ImpactBlast = nullptr;
public:	
	// Called every frame
	void LaunchProjectile(float Speed);

private:
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
