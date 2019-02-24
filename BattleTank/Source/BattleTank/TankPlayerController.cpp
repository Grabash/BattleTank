// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	if (!GetPawn()) return;

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

	// UE_LOG(LogTemp, Warning, TEXT("PlayerController ticking"));

}

//ATank* ATankPlayerController::GetControlledTank() const
//{
//	/*return Cast<ATank>(GetPawn());*/
//	return GetPawn();
//}

void ATankPlayerController::AimTowardsCrosshair()
{
	// if (!GetControlledTank()) { return; }

	if (!GetPawn()) { return; } // e.g. if not possesing

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	if (!ensure(GetPawn())) { return; }

	FVector HitLocation; // Out parameter

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	// UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation);

	if (bGotHitLocation) //Has "side-effect
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO Tell controlled tank to aim at this point

		AimingComponent->AimAt(HitLocation);
	}
	

}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

	FVector SightRayHitLocation;
	// FVector WorldLocation, WorldDirection;

	SightRayHitLocation = FVector(1.0);

	HitLocation = SightRayHitLocation;

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto CrosshairScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	// UE_LOG(LogTemp, Warning, TEXT("CrosshairScreenLocation: %s"), *CrosshairScreenLocation.ToString() );


	// "De-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(CrosshairScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
		// UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *(LookDirection.ToString()));

		// Line-trace along that look direction, and see what we hit (up to max range)


	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	auto PossessedTank = Cast<ATank>(GetPawn());

	if (!ensure (PossessedTank)) { return; }

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
}

void ATankPlayerController::OnPossessedTankDeath()
{
	auto PossessedTank = GetPawn();

	if (!ensure(PossessedTank)) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Received OnDeath broadcast from %s!"), *(PossessedTank->GetName()));
	StartSpectatingOnly();
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation,
		LookDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera
		))
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
		return false;
	


}



