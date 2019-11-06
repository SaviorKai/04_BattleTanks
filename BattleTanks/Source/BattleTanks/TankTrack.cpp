// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "TankTrack.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"								//for ASprungWheel
#include "PhysicsEngine/PhysicsConstraintComponent.h"	//for UPhysicsConstraintComponent

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
	// Initialize Required Arrays
	TArray<USceneComponent*> Children;
	TArray<UPhysicsConstraintComponent*> PhyConstraintsArray;
	TArray<ASprungWheel*> Wheels;															//The Final Array the function will return.

	//* Get the root component, and all its children, and place it into the Empty Array
	GetOwner()->GetRootComponent()->GetChildrenComponents(true, Children);					// OUT Parameter					

	//* While we can still find a component that is of type UPhysicsConstraintComponent, 
	//* add it to the PhyConstraintsArray, and remove it from the Children array
	//* until we can't find any.
	UPhysicsConstraintComponent* PhyConst = nullptr;										// OUT Parameter Value
	while (Children.FindItemByClass<UPhysicsConstraintComponent>(&PhyConst))				// OUT Parameter
	{
		PhyConstraintsArray.Add(PhyConst);
		Children.Remove(PhyConst);
	}
	
	//* Loop through the PhyConstraintsArray, and get their owners, 
	//* and add them to the Wheels Array. 
	//* These are ASprungWheel instances, which we need to return for this function.
	for (auto i : PhyConstraintsArray)
	{
		auto SingleWheel = Cast<ASprungWheel>(i->GetOwner());

		Wheels.Add(SingleWheel);
	}
		
	return Wheels;
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
	}
}
