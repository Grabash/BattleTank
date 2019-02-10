// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	// UE_LOG(LogTemp, Warning, TEXT("LeftTrack: %s RightTrack: %s"), *LeftTrack->GetName(), *RightTrack->GetName());
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality

	// auto TankName = GetOwner()->GetName();
	// auto MoveVelocityString = MoveVelocity.GetSafeNormal().ToString();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendTurnRight(RightThrow);

	

	// UE_LOG(LogTemp, Warning, TEXT("Tank name: %s  MoveVelocity: %s"), *TankName, *MoveVelocityString);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{

	if (!ensure(LeftTrack && RightTrack)) { return; }

	//auto Name = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw: %f"), Throw);
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}


