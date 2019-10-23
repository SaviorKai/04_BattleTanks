// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

#include "Engine/World.h"

void UTankMovementComponent::InitialiseMoveComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack) //NOTE!! THIS IS CALLED AND SETUP IN THE bp_Tank BeginPlay EventGraph
{
	if (!LeftTrack || !LeftTrack) { return; } ///Pointer Protection

	MyLeftTrack = LeftTrack;
	MyRightTrack = RightTrack;

}


void UTankMovementComponent::IntendMoveForward(float Amount)
{
	MyLeftTrack->SetThrottle(Amount);
	MyRightTrack->SetThrottle(Amount);
	UE_LOG(LogTemp, Warning, TEXT("%f: IntendMoveForward() called. Amount: %f"), GetWorld()->GetTimeSeconds(), Amount);
}