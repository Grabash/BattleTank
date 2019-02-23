// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BluePrintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets a throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; //Assume 40 tonne tank, and 1g acceleration

	// Hack used to tone the applied side force
	UPROPERTY(EditDefaultsOnly)
	float CorrectionForceMultiplier = 1.0f;

	UTankTrack();
	// virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//void ApplySidewaysForce();
	
	virtual void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels() const;
	
	
private:
	UFUNCTION()
	// void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DriveTrack(float CurrentThrottle);
	// float CurrentThrottle = 0;

	
};
