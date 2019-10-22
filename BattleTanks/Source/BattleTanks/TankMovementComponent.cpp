// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "Engine/World.h"

void UTankMovementComponent::IntendMoveForward(float Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: IntendMoveForward() called. Amount: %f"), GetWorld()->GetTimeSeconds(), Amount);
}


