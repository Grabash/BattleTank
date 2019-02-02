// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation)
{

		if (!ensure(Barrel || !Turret)) { return; }
	
		FVector OutLaunchVelocity(0);
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		auto OurTankName = GetOwner() -> GetName();
		auto BarrelLocation = Barrel->GetComponentLocation();

		// Calculate the OutLaunchVelocity
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
			
		if (ensure(bHaveAimSolution))
		{
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
			// UE_LOG(LogTemp, Warning, TEXT("%s fireing at %s"), *OurTankName, *AimDirection.ToString());

			MoveBarrelTowards(AimDirection);
			// MoveTurretTowards(AimDirection);

			//auto Time = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
		}
		//else {
		//	auto Time = GetWorld()->GetTimeSeconds();
		//	//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
		//}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel || !Turret)) { return; }

	// Work-out Difference between current barrel roation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	// Move the barrer to the right amount this frame
	// Give a max elevation speed, and the frame time

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

//void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
//{
//	// Work-out Difference between current turret roation and AimDirection
//	auto TurretRotator = Turret->GetForwardVector().Rotation();
//	auto AimAsRotator = AimDirection.Rotation();
//	auto DeltaRotator = AimAsRotator - TurretRotator;
//	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
//
//	// Move the turret to the right amount this frame
//	// Give a max elevation speed, and the frame time
//
//	Turret->Rotate(DeltaRotator.Yaw);
//}


