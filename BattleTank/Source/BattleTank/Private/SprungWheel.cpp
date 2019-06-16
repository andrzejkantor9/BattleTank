// Copyright info


#include "SprungWheel.h"

#include "Components/PrimitiveComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);
	Mass->SetNotifyRigidBodyCollision(true);
	Mass->SetVisibility(true);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->SetVisibility(true);

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	MassWheelConstraint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

