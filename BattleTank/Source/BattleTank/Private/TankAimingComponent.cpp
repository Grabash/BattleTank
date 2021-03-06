// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() 
{
	// So that first shot is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aiming Component ticking."));

	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}

	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}

	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

	// TODO Handle aiming and locked states

}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileBP)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	ProjectileBlueprint = ProjectileBP;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	//UE_LOG(LogTemp, Warning, TEXT("Barrel Forward Vector: %s Aim Direction: %s"), *(Barrel->GetForwardVector().ToString()), *(AimDirection.ToString()));
	if (!ensure(Barrel)) { return false; }

	return ((Barrel->GetForwardVector().Equals(AimDirection, 0.01f))) ? false : true;

	
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
			
		//if (ensure(bHaveAimSolution))
		if (bHaveAimSolution)
		{
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
			// UE_LOG(LogTemp, Warning, TEXT("%s fireing at %s"), *OurTankName, *AimDirection.ToString());

			MoveBarrelTowards(AimDirection);
			
		}
		
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

	// If Yaw > 180 then go opposite way
	// Yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}

	else 
	{
		// If Yaw > 180 then go opposite way
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}



void UTankAimingComponent::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank firing!"), Time);


	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("%f: No barrel found!"), Time);
		return;*/

		//if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		if (!ensure(Barrel)) { return; }

		if (!ensure(ProjectileBlueprint && ProjectileBlueprint->IsChildOf<AProjectile>())) { return; }

		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;

		//UE_LOG(LogTemp, Warning, TEXT("RoundsLeft: %i"), GetRoundsLeft());

	}

}

