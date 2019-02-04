// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// Super::TickComponent();
	// UE_LOG(LogTemp, Warning, TEXT("Track ticking."));

	
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Work-out the require acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	
	// Calculate and apply sideways force (F = m a )
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	// auto Time = GetWorld()->GetTimeSeconds();

	/*auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);*/

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//UE_LOG(LogTemp, Error, TEXT("Component: %s Force Applied: %s ForceLocation: %s TankRoot: %s"), *GetName(), *ForceApplied.ToString(), *ForceLocation.ToCompactString(), *TankRoot->GetName());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

