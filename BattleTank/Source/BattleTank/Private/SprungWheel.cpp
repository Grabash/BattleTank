// Copyright Orajt

#include "SprungWheel.h"
#include "Engine/StaticMesh.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	SetRootComponent(MassWheelConstraint);



	/*Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetupAttachment(MassWheelConstraint);
*/
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	// Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// or, possible in the constructor only?
	Wheel->SetupAttachment(MassWheelConstraint);

	



}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	
	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Null: %s"), *GetAttachParentActor()->GetName());
	}
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

