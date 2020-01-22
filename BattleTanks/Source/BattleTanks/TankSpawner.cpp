#include "TankSpawner.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Engine/TargetPoint.h"


// Sets default values
ATankSpawner::ATankSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer_SpawnInterval, this, &ATankSpawner::SpawnTanks, SpawnInterval, false, SpawnInterval);
}

void ATankSpawner::SpawnTanks()
{
	if (!TankSpawned) { return; }

	/// Get Spawn Points
	TArray<AActor*> SpawnPoint_Array;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoint_Array);
	if (SpawnPoint_Array.Num() < 1) { return; }

	/// Select random spawn point from array
	int32 SPointsCount = SpawnPoint_Array.Num();
	int32 SelectedPoint = FMath::RandRange(0, SPointsCount - 1);			//We -1 here, since the array starts at 0 for accessing, but the .Num() count starts at 1.
	auto SpawnLocation = SpawnPoint_Array[SelectedPoint]->GetActorLocation();

	/// Spawn Tank
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	GetWorld()->SpawnActor<ATank>(TankSpawned, SpawnLocation, SpawnLocation.Rotation(), SpawnParams);

	/// Reduce Spawntime for next Tank, and clamp to 5sec
	if (SpawnInterval > 5.0f)
	{
		SpawnInterval -= 1.0f;
	}

	/// Restart Timer
	GetWorldTimerManager().SetTimer(Timer_SpawnInterval, this, &ATankSpawner::SpawnTanks, SpawnInterval, false, SpawnInterval);


}

