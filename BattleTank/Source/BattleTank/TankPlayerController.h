// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an Out parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LineTraceRange = 1000000;


	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector StartLocation, FVector&) const;

	//ATank* GetPlayerTank() const;
	
};
