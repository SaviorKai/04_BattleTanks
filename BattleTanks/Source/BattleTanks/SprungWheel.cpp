// All rights reserved © 2019 Ivan Carl Engelbrecht

// TODO: Make the SprungWheel delete itself when it's owner tank dies.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h" // For Static Mesh Components
#include "PhysicsEngine/PhysicsConstraintComponent.h" // For Physics Constraints
#include "Components/SphereComponent.h" //For USphereComponent type


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//* IVAN NOTE: TICK GROUPS!
	//* BLUEPRINT: When can change when this Actor Tick() even takes place, by going into the blueprint, 
	//* selecting the actor, and on the details, in the Actor Tick, click the dropdown and change it as required.
	//* C++: In the constructor code:
	PrimaryActorTick.TickGroup = TG_PostPhysics;												// Also do a if (GetWorld()->TickGroup == TG_PostPhysics) in the tick, to ensure it's correctly set.

	
	/// Add the Physics Constraint Component (SPRING)
	SpringPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint(Spring)"));
	SetRootComponent(SpringPhysicsConstraint);													// Make it the root component. 
	SpringPhysicsConstraint->SetAngularSwing1Limit(ACM_Locked, 0);								// ACM = Angular Constraint
	SpringPhysicsConstraint->SetAngularSwing2Limit(ACM_Locked, 0);
	SpringPhysicsConstraint->SetAngularTwistLimit(ACM_Locked, 0);
	SpringPhysicsConstraint->SetLinearZLimit(LCM_Free, 300);									// LCM = Linear Constraint (Z Motion)
	SpringPhysicsConstraint->SetLinearPositionDrive(false, false, true);						// Linear Motor: Turn on Position Z
	SpringPhysicsConstraint->SetLinearVelocityDrive(false, false, true);						// Linear Motor: Turn on Velocity Z
	SpringPhysicsConstraint->SetLinearDriveParams(120.0f, 60.0f, 0);								// Linear Motor: Position and Velocity Strength
	//NOTE: SpringPhysicsConstraint->SetConstrainedComponents is set in BeginPlay(), to connect the first component with the tank.

	/// Add the Axle Mesh component for the spring
	AxleMesh = CreateDefaultSubobject<USphereComponent>(FName("AxleMesh"));						// We are using USphereComponenthere, as they can be invisible if we want (no mesh)
	AxleMesh->SetupAttachment(SpringPhysicsConstraint);											// Better way of attaching components.
	AxleMesh->SetSimulatePhysics(true);
	AxleMesh->SetMassOverrideInKg(NAME_None, 10000.0f, true);									// Override and set mass.
	//NOTE: In bp, set: -Collision Presets : Overlap All > Custom.Collisions Enabled(Query and Physics)
	//NOTE: In bp, set: -Axel Mesh = Z: -75


	/// Add the AxlePhysics Constraint
	AxlePhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint(Axle)"));
	AxlePhysicsConstraint->SetupAttachment(AxleMesh);
	AxlePhysicsConstraint->SetAngularSwing1Limit(ACM_Locked, 0);								// ACM = Angular Constraint
	AxlePhysicsConstraint->SetAngularSwing2Limit(ACM_Free, 0);									// This is the one we free for the correct rotation forward.
	AxlePhysicsConstraint->SetAngularTwistLimit(ACM_Locked, 0);									// Twist Motion
	
	/// Add the Wheel Mesh component for the spring
	WheelMesh = CreateDefaultSubobject<USphereComponent>(FName("WheelMesh"));					// We are using USphereComponenthere, as they can be invisible if we want (no mesh)
	WheelMesh->SetupAttachment(AxleMesh);														// Better way of attaching components.
	WheelMesh->SetSimulatePhysics(true);
	WheelMesh->SetMassOverrideInKg(NAME_None, 1000.0f, true);									// Override and set mass.
	//NOTE: In bp, set: PhysicsActor (collision)
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	//1. Register our OnHit() Delegate, by calling the UE4 function on the mesh, names OnComponentHit.AddDynamic()
	WheelMesh->SetNotifyRigidBodyCollision(true);												// This always turns on "Simulation Generates Hit Events" checkbox as default.  			
	WheelMesh->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);							// Remember that we're passing the '&'address of the function to the OnHitComponent, to call it WHEN it gets hit, and not calling it now.

	SetupConstraint();   ///Sets up our Spring 
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetWorld()->TickGroup == TG_PostPhysics)			// Check to ensure the group is correct, since we've changed it a the top and also before changing values at the wrong time.
	{
		CurrentDrivingForce = 0.0f;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("SprungWheel has the incorrect TickGroup set! It needs to be TG_PostPhysics"));
		PrimaryActorTick.TickGroup = TG_PostPhysics;
	}
}

void ASprungWheel::SetupConstraint()
{
	auto MyParentActor = GetAttachParentActor();													// Gets the Root Component, Then the Component its attached too, Then gets the Owner of that Compoent (Tank) //NOTE: Only actors (not USceneComponents) can call this function.
	if (MyParentActor)	//Pointer Protection
	{
		//Set the Contraints settings to Component 1 = Tank Root, Component 2 = Axle
		auto BodyRoot_Converted = Cast<UPrimitiveComponent>(MyParentActor->GetRootComponent());		//Convert to UPrimitiveComponent
		auto AxleMesh_Converted = Cast<UPrimitiveComponent>(AxleMesh);								//Convert to UPrimitiveComponent
		SpringPhysicsConstraint->SetConstrainedComponents(
			BodyRoot_Converted,
			NAME_None,
			AxleMesh_Converted,
			NAME_None
		);

		//Set the Contraints settings to Component 1 = Axle, Component 2 = Wheel
		auto WheelMesh_Converted = Cast<UPrimitiveComponent>(WheelMesh);							//Convert to UPrimitiveComponent
		AxlePhysicsConstraint->SetConstrainedComponents(											//Set the Contraints settings to Component 1 = Tank Root, Component 2 = AxleMesh
			AxleMesh_Converted,
			NAME_None,
			WheelMesh_Converted,
			NAME_None
		);
	}
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Apply Force
	WheelMesh->AddForce(AxleMesh->GetForwardVector() * (CurrentDrivingForce));     //Note: You can extract this as an "ApplyForce()" function, but why, its only 1 line.
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentDrivingForce += ForceMagnitude;
	
}