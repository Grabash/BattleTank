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
		 UE_LOG(LogTemp, Warning, TEXT("Possessed Tank: %s"), *ControlledTank);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nulptr, no Tank possessed!"));
	}

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

