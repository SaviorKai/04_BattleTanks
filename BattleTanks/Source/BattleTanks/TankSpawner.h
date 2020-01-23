

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankSpawner.generated.h"

class ATank;

UCLASS()
class BATTLETANKS_API ATankSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ATank> TankSpawned; 

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float SpawnInterval = 20.0f;

private:
	void SpawnTanks();
	
	FTimerHandle Timer_GameStart;
	FTimerHandle Timer_SpawnInterval;

};
