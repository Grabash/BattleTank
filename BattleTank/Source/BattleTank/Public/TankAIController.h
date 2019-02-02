// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "Public/Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.generated.h"

/**
 * 
 */
 class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	void Tick(float DeltaTime) override;

	// How close can the AI tank get
	float AcceptanceRadius = 3000;
public:
	void BeginPlay() override;
	/*ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;*/
};
