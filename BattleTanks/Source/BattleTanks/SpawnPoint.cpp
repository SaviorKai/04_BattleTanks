// Copyright Ivan Carl Engelbrecht


#include "SpawnPoint.h"
#include "Engine/World.h"			// So we can use GetWorld()
#include "GameFramework/Actor.h"	// So we can use GetAttachParentActor()

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
	auto NewActor = GetWorld()->SpawnActor<AActor>(SpawnClass);									//SpawnClass is a var we've created in the header file.
	if (NewActor)																				//Pointer Protection
	{
		NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);	//This attaches something to the "NewActor", not "NewActor" to something.
	}
	
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

