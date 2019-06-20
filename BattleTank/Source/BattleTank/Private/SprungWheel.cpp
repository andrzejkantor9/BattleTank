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
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	//Axle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//Axle->SetNotifyRigidBodyCollision(true);
	//Axle->SetVisibility(true);

	//Axle->SetSimulatePhysics(true);
	//Axle->SetEnableGravity(true);
	//Axle->SetMassOverrideInKg(NAME_None, 400000.f, true);

	//Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	//Wheel->SetNotifyRigidBodyCollision(true);
	//Wheel->SetVisibility(true);

	//Wheel->SetSimulatePhysics(true);
	//Wheel->SetEnableGravity(true);
	//Wheel->SetMassOverrideInKg(NAME_None, 400000.f, true);

	//AxleWheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);

	//MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 1.f);
	//MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 1.f);
	//MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 1.f);
	//MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 1.f);
	//MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	//MassWheelConstraint->SetLinearVelocityDrive(false, false, true);

	//MassWheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(GetAttachParentActor()), NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	if (!Axle) 
	{
		UE_LOG(LogTemp, Error, TEXT("Axle not present."));
		return;
	}
	if (!Wheel)
	{
		UE_LOG(LogTemp, Error, TEXT("Wheel not present."));
		return;
	}
	if (!MassWheelConstraint)
	{
		UE_LOG(LogTemp, Error, TEXT("MassWheelConstraint not present."));
		return;
	}
	if (!AxleWheelConstraint)
	{
		UE_LOG(LogTemp, Error, TEXT("AxleWheelConstraint not present."));
		return;
	}
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrane);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup = TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrane = 0.f;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrane += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnHit: %f"), GetWorld()->GetTimeSeconds());
	ApplyForce();
}