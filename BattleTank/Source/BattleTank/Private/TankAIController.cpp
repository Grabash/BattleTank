// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank> (GetPawn());

}

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	ATank* p_ControlledTank = GetControlledTank();

	/*if (!p_ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr, no tank possessed."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController: %s"), *(p_ControlledTank->GetName()));
	}

	if (!GetPlayerTank()) {
		UE_LOG(LogTemp, Warning, TEXT("AIController couldn't find Player's tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found Player's Tank: %s"), *(GetPlayerTank()->GetName()));
	}*/
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (GetPlayerTank())
	{
		// TODO Move towards the player


		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}

	
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* p_PlayerTank = nullptr;

	if (GetWorld()->GetFirstPlayerController())
	{
		p_PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		return p_PlayerTank;
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("Nullptr, no PlayerController."));
		return nullptr;
	}
	
}

