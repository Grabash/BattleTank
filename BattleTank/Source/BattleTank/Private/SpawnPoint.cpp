// Copyright Orajt

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// auto NewActor = GetWorld()->SpawnActor<AActor>(SpawnClass);

	// TODO Change SpawnActor to SpawnActorDeferred to stop SprungWheel's BeginPlay() from running before this BeginPlay() by not running
	// BP construction scripts

	// Actually done but keeping bookmark

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	

	if (!SpawnedActor) return;

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	// finishing spawning and calling BeginPlay()
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor * USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

