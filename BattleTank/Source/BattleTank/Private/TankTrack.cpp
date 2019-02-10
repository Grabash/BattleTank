// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s OnHit event."), *GetName());
	// UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"));

	// Drive the tracks
	// Apply sideways force

	DriveTrack();
	ApplySidewaysForce();

	// Reset Throttle
	 CurrentThrottle = 0;

}



void UTankTrack::ApplySidewaysForce()
{
	// Work-out the require acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways force (F = m a )
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks

	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce pre multiplier: %s"), *CorrectionForce.ToString());

	// Adding a parameter to modify the force from blueprint.
	CorrectionForce = CorrectionForce * CorrectionForceMultiplier;

	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce after multiplier: %s"), *CorrectionForce.ToString());

	 TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);

	// TODO Check this
	DriveTrack();
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

