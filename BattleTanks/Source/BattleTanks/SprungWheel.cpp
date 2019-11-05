// Copyright Ivan Carl Engelbrecht


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h" // For Static Mesh Components
#include "PhysicsEngine/PhysicsConstraintComponent.h" // For Physics Constraints


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Add the root mesh component
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MassMesh"));
	SetRootComponent(Cast<USceneComponent>(RootMesh));									//We set the Root component here, to ensure it doesn't accidentally make something else the root.
	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetMassOverrideInKg(NAME_None, 40000.0f, true);							// Override and set mass.


	/// Add the second Mesh component for the spring
	WheelConstraintMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelConstraintMesh"));
	WheelConstraintMesh->SetupAttachment(RootMesh);										// Better way of attaching components.
	WheelConstraintMesh->SetSimulatePhysics(true);
	WheelConstraintMesh->SetMassOverrideInKg(NAME_None, 10000.0f, true);				// Override and set mass.

	/// Add the Physics Constraint Component (SPRING)
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint(Spring)"));
	PhysicsConstraint->SetupAttachment(RootMesh);										// Better way of attaching components.
	PhysicsConstraint->SetAngularSwing1Limit(ACM_Locked, 0);							// ACM = Angular Constraint
	PhysicsConstraint->SetAngularSwing2Limit(ACM_Locked, 0);				
	PhysicsConstraint->SetAngularTwistLimit(ACM_Locked, 0);					
	PhysicsConstraint->SetLinearZLimit(LCM_Limited, 300);								// LCM = Linear Constraint
	PhysicsConstraint->SetLinearPositionDrive(false, false, true);						// Linear Motor: Turn on Position Z
	PhysicsConstraint->SetLinearVelocityDrive(false, false, true);						// Linear Motor: Turn on Velocity Z
	PhysicsConstraint->SetLinearDriveParams(50.0f, 25.0f, 0);							// Linear Motor: Position and Velocity Strength
	PhysicsConstraint->ComponentName1.ComponentName = TEXT("MassMesh");					// Set Component 1 for spring
	PhysicsConstraint->ComponentName2.ComponentName = TEXT("WheelConstraintMesh");		// Set Component 2 for spring


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

