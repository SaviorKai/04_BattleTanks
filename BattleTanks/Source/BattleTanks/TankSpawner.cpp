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

	SpawnTanks();
}

void ATankSpawner::SpawnTanks()
{
	if (!TankSpawned) { return; }

	/// Get Spawn Points
	TArray<AActor*> SpawnPoint_Array;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoint_Array);
	if (SpawnPoint_Array.Num() < 1) { return; }

	int32 SPointsCount = SpawnPoint_Array.Num();
	int32 SelectedPoint = FMath::RandRange(1, SPointsCount);
	auto SpawnLocation = SpawnPoint_Array[SelectedPoint]->GetActorLocation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor<ATank>(TankSpawned, SpawnLocation, SpawnLocation.Rotation(), SpawnParams);
}




