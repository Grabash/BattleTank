// Copyright Orajt

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const;

	// Config
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

	// Cant really find the SprungWheel_BP class in C++?
	//TSubclassOf<AActor> SpawnClass = ASprungWheel::StaticClass();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
private:
	UPROPERTY()
		AActor* SpawnedActor = nullptr;

		
};
