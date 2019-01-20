// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

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

