// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	if (GetControlledTank() != nullptr)
	{
		FString ControlledTank = GetControlledTank()->GetName();
		 UE_LOG(LogTemp, Warning, TEXT("TankPlayerController: %s"), *ControlledTank);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nulptr, no Tank possessed!"));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

	// UE_LOG(LogTemp, Warning, TEXT("PlayerController ticking"));

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect
	{
	//	UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO Tell controlled tank to aim at this point
	}
	

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {

	FVector SightRayHitLocation;

	SightRayHitLocation = FVector(1.0);

	OutHitLocation = SightRayHitLocation;

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto CrosshairScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// UE_LOG(LogTemp, Warning, TEXT("CrosshairScreenLocation: %s"), *CrosshairScreenLocation.ToString() );


	// "De-project" the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to max range)


	return true;

}



