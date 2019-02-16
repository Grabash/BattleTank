// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//#include "TankAimingComponent.h"
//#include "TankMovementComponent.h"
//#include "TankBarrel.h"
//#include "Projectile.h"

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

//void ATank::OnDeath()
//{
//}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// UE_LOG(LogTemp, Warning, TEXT("[%s] e8dd6798: Tank Constructor called."), *GetName())

	// No need to protect points as added at construction

	// 
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}


float ATank::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
	AActor * DamageCauser
)
{
	/*float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Clamp<float>(DamageToApply, 0.0f, Health);


	UE_LOG(LogTemp, Warning, TEXT("Damage Amount: %f DamageToApply: %f"), DamageAmount, DamageToApply);

	Health = Health - DamageToApply;*/

	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
		//UE_LOG(LogTemp, Warning, TEXT("Tank is destroyed."));

		OnDeath.Broadcast();

	//UE_LOG(LogTemp, Warning, TEXT("DamageAmount=  %f DamageToApply= %i"), DamageAmount, DamageToApply);

	return DamageToApply;

}

// Called when the game starts or when spawned
//void ATank::BeginPlay()
//{
//	Super::BeginPlay(); // Needed for BP BeginPlay to run!
//
//	// UE_LOG(LogTemp, Warning, TEXT("[%s] e8dd6798: Tank Begin Play called."), *GetName());
//
//	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
//	
//}





//void ATank::AimAt(FVector HitLocation)
//{
//	if (!ensure(TankAimingComponent)) { return; }
//
//	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
//	//auto OurTankName = GetName();
//	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString());
//}

// Setting Turret and Barrel moved to AimingComponent
//void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
//{
//	TankAimingComponent->SetBarrelReference(BarrelToSet);
//	Barrel = BarrelToSet;
//}
//
//void ATank::SetTurretReference(UTankTurret* TurretToSet)
//{
//	TankAimingComponent->SetTurretReference(TurretToSet);
//}

//void ATank::Fire()
//{
//	auto Time = GetWorld()->GetTimeSeconds();
//	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank firing!"), Time);
//
//	if (!ensure(Barrel)) { return; }
//
//	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
//
//	if (isReloaded) 
//	{
//		/*UE_LOG(LogTemp, Warning, TEXT("%f: No barrel found!"), Time);
//		return;*/
//
//		// Spawn a projectile at the socket location on the barrel
//		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
//			ProjectileBlueprint,
//			Barrel->GetSocketLocation(FName("Projectile")),
//			Barrel->GetSocketRotation(FName("Projectile"))
//			);
//
//		Projectile->LaunchProjectile(LaunchSpeed);
//		LastFireTime = FPlatformTime::Seconds();
//
//	}
//
//}

