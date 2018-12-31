// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// Given a max rotation speed, and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	// auto Rotation = FMath::Clamp<float>(RawNewRotation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(0, 0, RawNewRotation));
}