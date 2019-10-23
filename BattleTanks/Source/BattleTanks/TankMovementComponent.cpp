// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

#include "Engine/World.h"

void UTankMovementComponent::InitialiseMoveComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack) //NOTE!! THIS IS CALLED AND SETUP IN THE bp_Tank BeginPlay EventGraph
{
	if (!LeftTrack || !LeftTrack) ///Pointer Protection Log only (Protection not needed, but added for the log.)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULLPTR on TankMovementComponent::InitialiseMoveComponent()"));;
	}

	MyLeftTrack = LeftTrack;
	MyRightTrack = RightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);   //Removed super, since we'll be replacing it. 

	/** TODO: Understand how this function was called????? 
	// (It seems the AAIActor::MoveToActor() function engine code, calls RequestDirectMove() as part of its function. 
	// This is why we've overridden it. Our version gets called, because we didn't use SUPER and replaced the root.)
	*/
	auto MyTank = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%f: RequestDirectMove() called on %s, MoveVelocity: %s"), GetWorld()->GetTimeSeconds(), *MyTank, *MoveVelocityString);
}


void UTankMovementComponent::IntendMoveForward(float Amount)
{
	if (!MyLeftTrack || !MyLeftTrack) { return; } // Pointer Protection
	MyLeftTrack->SetThrottle(Amount);
	MyRightTrack->SetThrottle(Amount);
	

	// Clamp Throttle to avoid DOUBLE-SPEED from dual input.

}

void UTankMovementComponent::IntendTurnRight(float Amount)
{
	if (!MyLeftTrack || !MyLeftTrack) { return; } // Pointer Protection
	MyLeftTrack->SetThrottle(Amount);
	MyRightTrack->SetThrottle(-Amount);

	// Clamp Throttle to avoid DOUBLE-SPEED from dual input.
}
