// Copyright Orajt

#include "SprungWheel.h"
#include "Engine/StaticMesh.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);


	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	// Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// or, possible in the constructor only?
	Wheel->SetupAttachment(Axle);

	

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle);




}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true); // Generate OnHit Events
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);


	SetupConstraint();
	
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}

	// UE_LOG(LogTemp, Warning, TEXT("%s Tick: %f"), *(this->GetName()), GetWorld()->GetTimeSeconds());
	
	

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	// Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
	
	TotalForceMagnitudeThisFrame += ForceMagnitude;

}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{

	/*if (this)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s OnHit: %f"), *(this->GetName()), GetWorld()->GetTimeSeconds());
	}
*/

	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

