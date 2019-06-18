// Copyright info


#include "SprungWheel.h"

#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Axle->SetNotifyRigidBodyCollision(true);
	Axle->SetVisibility(true);

	Axle->SetSimulatePhysics(true);
	Axle->SetEnableGravity(true);
	Axle->SetMassOverrideInKg(NAME_None, 400000.f, true);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	//Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetupAttachment(Axle);
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->SetVisibility(true);

	Wheel->SetSimulatePhysics(true);
	Wheel->SetEnableGravity(true);
	Wheel->SetMassOverrideInKg(NAME_None, 400000.f, true);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	//AxleWheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	AxleWheelConstraint->SetupAttachment(Axle);

	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 1.f);
	MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 1.f);
	MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 1.f);
	MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 1.f);
	MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	MassWheelConstraint->SetLinearVelocityDrive(false, false, true);

	//MassWheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(GetAttachParentActor()), NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();

	//AttachToComponent();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

