// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	UE_LOG(LogTemp, Warning, TEXT("LeftTrack: %s RightTrack: %s"), *LeftTrack->GetName(), *RightTrack->GetName());
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{

	if (!LeftTrack || !RightTrack) { return; }

	//auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	

	/*if (Throw < 0)
	{
		Throw = Throw /2.0f;
	}*/

	/*if (Throw != 0.0f)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}*/

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO Prevent double-speed due to dual control use

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw: %f"), Throw);
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

//void UTankMovementComponent::IntendTurnLeft(float Throw)
//{
//	LeftTrack->SetThrottle(-Throw);
//	RightTrack->SetThrottle(Throw);
//}

