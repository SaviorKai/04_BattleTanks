// Copyright Ivan Carl Engelbrecht


#include "SpawnPoint.h"
#include "Engine/World.h"			// So we can use GetWorld()
#include "GameFramework/Actor.h"	// So we can use GetAttachParentActor()
#include "Kismet/GameplayStatics.h" // So we can use FinishSpawningActor()

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	//Create a new Actor, and attach the root component, to this new actor.
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());		//SpawnActorDeferred, deferrs the BeginPlay() code, so that it only runs when we call it with UGameplayStatics::FinishSpawningActor()//NOTE: SpawnClass is a var we've created in the header file.
	
	if (NewActor)																					//Pointer Protection
	{
		NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);			//This attaches something to the "NewActor", not "NewActor" to something.
		UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());					//Finishes the spawn of the actor, by running it's BeginPlay() code now.
	}
	
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

