// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "TankTrack.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"								//for ASprungWheel
#include "SpawnPoint.h"									//for USpawnPoint
#include "Components/SphereComponent.h" //For USphereComponent type
#include "GameFramework/Actor.h"

UTankTrack::UTankTrack()
{
	//Tick "Simulation Generates Overlap Events"
	SetNotifyRigidBodyCollision(true);

	//Set Liner Dampening to 0.
	SetLinearDamping(0.0f);

	//SetMesh
	UStaticMesh* TrackMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Units/Tank/Meshes/tank_fbx_Track.tank_fbx_Track"));
	if (TrackMesh != nullptr)
	{
		//Add mesh
		SetStaticMesh(TrackMesh);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank couldn't find the Track Mesh to add it. Check Tank.cpp file location."));
	}


	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	/// NEW SOLUTION
	TArray<ASprungWheel*> SprungWheelsArray;												// Final Return Array

	// Find the children of THIS TRACK (Should only be spawnpoints)
	TArray<USceneComponent*> ChildrenArray;
	GetChildrenComponents(true, ChildrenArray);												// OUT Parameter
	
	// Loop through each Child,
	for (auto i : ChildrenArray)
	{
		// Cast them to the correct type
		auto ChildSpawnPoint = Cast<USpawnPoint>(i);
		if (!ChildSpawnPoint) continue;														//NULLPTR Protection Incase cast fails. (Continue resumes the for loop)
		
		// Call the GetSpawnActor() method
		auto ChildSprungWheel = ChildSpawnPoint->GetSpawnedActor();
		if (!ChildSprungWheel) continue;													//NULLPTR Protection (Continue resumes the for loop)
		
		// Cast the AActor result, to the correct type
		auto SprungWheel = Cast<ASprungWheel>(ChildSprungWheel);

		// Add the SprungWheel to the final result array.
		SprungWheelsArray.Add(SprungWheel);
	}

	return SprungWheelsArray;
	
}

void UTankTrack::SetThrottle(float Amount)
{
	//Clamp Throttle (Throttle is set as a var in the header, so that we can get it's current value.
	auto Throttle = FMath::Clamp<float>(Amount, -1,1);
	DriveTrack(Throttle);
}

void UTankTrack::DriveTrack(float Throttle)
{
	auto ForceApplied = Throttle * TrackMaxDrivingForce;
	auto AllWheels = GetWheels();												// Gets all the wheels on the tank
	
	if (AllWheels.Num() != 0)													//NULLPTR Protection
	{
		auto ForcePerWheel = ForceApplied / AllWheels.Num();					// Figures out the driving force per wheel, by dividing the Force Applied by the Num of items in the array.
		
		for (ASprungWheel* Wheel : AllWheels)									// for (item in: WheelsArray) - We set the item type to be ASprungWheel type and made it a varible "Wheel"
		{
			Wheel->AddDrivingForce(ForcePerWheel);								// Calls the AddDrivingForce() on the SprungWheel Class object, and gives it the driving force.
		}
		
		RotateMeshWheels();
	}
}

void UTankTrack::SetupMeshWheels()
{
	/// Setup My Main Wheel
	auto MySpawnSpring = GetChildComponent(1);
	if (!MySpawnSpring) { return; }

	TArray<USceneComponent*> ChildrenComps;
	MySpawnSpring->GetChildrenComponents(true, ChildrenComps);
	if (ChildrenComps.Num() <= 0) { return; }

	AActor* MyOwner = ChildrenComps[0]->GetOwner();
	TArray<USphereComponent*> SpringChildrenComps;
	MyOwner->GetComponents(SpringChildrenComps);
	if (SpringChildrenComps.Num() <= 0) { return; }

	MyMainWheel = Cast<USphereComponent>(SpringChildrenComps[1]);


	/// Add Mesh Wheels to Array
	TArray<USceneComponent*> TrackChildren;
	GetChildrenComponents(false, TrackChildren);
	if (TrackChildren.Num() <= 0) { return; }

	for (auto i : TrackChildren)
	{
		auto Item = Cast<UStaticMeshComponent>(i);
		if (Item)
		{
			MeshWheels.Add(Item);
		}
	}
}

void UTankTrack::RotateMeshWheels()
{
	if (!MyMainWheel) 
	{ 
		SetupMeshWheels();
	}

	if (!MyMainWheel) { return; }
	
	auto NewRotation = MyMainWheel->RelativeRotation;

	for (auto i : MeshWheels)
	{
		i->RelativeRotation.Pitch = NewRotation.Roll;
	}
}
