// All rights reserved � 2019 Ivan Carl Engelbrecht


#include "SpawnPoint.h"
#include "Engine/World.h"			// So we can use GetWorld()
#include "GameFramework/Actor.h"	// So we can use GetAttachParentActor()
#include "Kismet/GameplayStatics.h" // So we can use FinishSpawningActor()

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	//Create a new Actor, and attach the root component, to this new actor.
	//SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());		//SpawnActorDeferred, deferrs the BeginPlay() code, so that it only runs when we call it with UGameplayStatics::FinishSpawningActor()//NOTE: SpawnClass is a var we've created in the header file.
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform(),GetOwner());

	//TODO: Test GetComponentTransform() and GetRelativeTransform(), including the FAttachmentTransformRules::KeepWorldTransform and FAttachmentTransformRules::KeepRelativeTransform rules.

	if (SpawnedActor)																						//Pointer Protection
	{
		SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);				//This Attaches the RootComponent of this Actor to the supplied component, optionally at a named socket.
		UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());						//Finishes the spawn of the actor, by running it's BeginPlay() code now.
	}
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* USpawnPoint::GetSpawnedActor() const
{
	if (SpawnedActor) // NULLPTR Protection
	{
		return SpawnedActor;
	}

	return nullptr;
}