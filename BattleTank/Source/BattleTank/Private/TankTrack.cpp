// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	// OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;  // OUT

	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}

//void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
//{
//	
//	DriveTrack();
//	ApplySidewaysForce();
//
//	// Reset Throttle
//	 CurrentThrottle = 0;
//
//}



//void UTankTrack::ApplySidewaysForce()
//{
//	// Work-out the require acceleration this frame to correct
//	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
//
//	// Calculate and apply sideways force (F = m a )
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
//
//	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce pre multiplier: %s"), *CorrectionForce.ToString());
//
//	// Adding a parameter to modify the force from blueprint.
//	CorrectionForce = CorrectionForce * CorrectionForceMultiplier;
//
//	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce after multiplier: %s"), *CorrectionForce.ToString());
//
//	 TankRoot->AddForce(CorrectionForce);
//}


void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);

	// TODO CHECK THIS! It might have been missing, but maybe it is added to early... >_>
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}

}

