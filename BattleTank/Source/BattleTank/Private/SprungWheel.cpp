// Copyright info


#include "SprungWheel.h"

#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	SetRootComponent(MassWheelConstraint);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Mass->SetNotifyRigidBodyCollision(true);
	Mass->SetVisibility(true);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->SetVisibility(true);

	Mass->SetSimulatePhysics(true);
	Mass->SetEnableGravity(true);
	Mass->SetMassOverrideInKg(NAME_None, 100.f, true);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetEnableGravity(true);
	Wheel->SetMassOverrideInKg(NAME_None, 1.f, true);

	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 1.f);
	MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 1.f);
	MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 1.f);
	MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 1.f);
	MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	MassWheelConstraint->SetLinearVelocityDrive(false, false, true);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (!GetAttachParentActor() )
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL"));
	}
	//AttachToComponent();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

