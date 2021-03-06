// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"
//#include "Tank.h"


void ATankAIController::BeginPlay() 
{

	Super::BeginPlay();

	//ATank* p_ControlledTank = GetControlledTank();
}

// Handling delegate in SetPawn because Constructor and BeginPlay() may race and be called too early

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}


}

void ATankAIController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Received OnDeath broadcast from %s!"), *(GetPawn()->GetName()));
	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	// if (GetWorld()->GetFirstPlayerController())
	//if (GetWorld()->GetFirstPlayerController() != NULL)
	//{
		auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		//ATank* ControlledTank = Cast<ATank>(GetPawn());
		auto ControlledTank = GetPawn();

		if (!(PlayerTank && ControlledTank)) { return; }
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters


		// Aim towards the player
		if (!(AimingComponent)) return;

		//ControlledTank->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// If aim or locked
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();  // TODO limit firing rate
		}
		
	//}


}


