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

	// UE_LOG(LogTemp, Warning, TEXT("%f: IntendMoveForward() called. Amount: %f"), GetWorld()->GetTimeSeconds(), Amount);
}
