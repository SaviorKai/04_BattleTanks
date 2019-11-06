// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitialiseMoveComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack) //IVAN NOTE!! THIS IS CALLED AND SETUP IN THE bp_Tank BeginPlay EventGraph
{
	MyLeftTrack = LeftTrack;
	MyRightTrack = RightTrack;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)  /// IVAN NOTE: This function is called by 'MoveToActor() UE4 function' used in the TankAIController.cpp file.
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);   //Removed super, since we'll be replacing it. 

	/// AI TANK MOVEMENT ///
	
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();    // IVAN NOTE: To 'GetForwardVector()' of a AActor, we need to use 'GetActorForwardVector()'. We also need to normalize it again, with GetSafeNormal();
	auto AIMoveDirection = MoveVelocity.GetSafeNormal();

	/// Move the AI tank 
	// Using DotProduct, get the speed based on the angle difference.         //TODO: Understand Vector Math Better (Creation in Unreal, Rotation, Direction(Forward Vector), Lenght, etc.
	auto DotProductResult = FVector::DotProduct(TankForwardDirection, AIMoveDirection); /// IVAN NOTE: This is a math solution that can be used on a vector. See lecture bookmark and read here: https://en.wikipedia.org/wiki/Dot_product#Geometric_definition
	IntendMoveForward(DotProductResult);

	/// Turn the AI Tank
	//Using the CrossProduct, get the speed we want to turn based on perpendicular length returned on the Z perp line.
	auto CrossProductResult = FVector::CrossProduct(TankForwardDirection, AIMoveDirection).Z; /// IVAN NOTE: Remember that its the Z value we want. The Z value will grow or shrink based on the angle difference.
	IntendTurnRight(CrossProductResult); 

	/* IVAN NOTE:
	// This function 'RequestDirectMove()' is called by 'MoveToActor() UE4 function' used in the TankAIController.cpp file.
	// (It seems the AAIActor::MoveToActor() function engine code, calls RequestDirectMove() as part of its function.
	// This is why we've overridden it, since we only want the velocity for direction. Our version gets called, because we didn't use SUPER and replaced the root.)
	*/
}


void UTankMovementComponent::IntendMoveForward(float Amount)
{
	if (!ensure(MyLeftTrack && MyRightTrack)) { return; } // NULLPTR Protection

	MyLeftTrack->SetThrottle(Amount);
	MyRightTrack->SetThrottle(Amount);
}

void UTankMovementComponent::IntendTurnRight(float Amount)
{
	if (!ensure(MyLeftTrack && MyRightTrack)) { return; } // NULLPTR Protection
	MyLeftTrack->SetThrottle(Amount);
	MyRightTrack->SetThrottle(-Amount);
}
