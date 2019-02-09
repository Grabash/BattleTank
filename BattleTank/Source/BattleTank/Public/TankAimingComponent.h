// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enums

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading

};


// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileBP); //Added Projectile class selection to Initlaize due to a bug(?) with resetting blueprints


	UFUNCTION(BlueprintCallable)
	void Fire();

	// TODO add SetTurretReference

	//void AimAt(FVector HitLocation, float LaunchSpeed);
	void AimAt(FVector HitLocation);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	EFiringState GetFiringState() const;

protected:
	

	// TODO remove once firing is moved to Aiming Component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	double LastFireTime = 0;
	FVector AimDirection;


private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual bool IsBarrelMoving();

	




		
};
