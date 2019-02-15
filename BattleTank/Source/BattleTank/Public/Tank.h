// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// #include "TankAimingComponent.h"
#include "Tank.generated.h"

//class UTankBarrel;
//class UTankTurret;
// class UTankAimingComponent;
// class UTankMovementComponent;
//class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// Returns current healtsh as a percentage of starting health, between 0 and 1

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	

private:

	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;


	// Called when the game starts or when spawned
	// virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// void BeginPlay();



	/*UFUNCTION(BlueprintCallable)
		void Fire();*/

	// TODO remove once firing is moved to Aiming Component
	/*UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;*/

	/*UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;*/
	//UClass* ProjectileBlueprint;

	// Local barrel reference for spawning projectile
	//  UTankBarrel* Barrel = nullptr; //TODO Remove

	
	// double LastFireTime = 0;

	/*UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;*/

	/*UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;*/


};
