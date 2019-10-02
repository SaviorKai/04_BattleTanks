// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin play called!"));

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) //Crash Protection (Pointer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed Actor: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullpointer on PlayerController - No Controlled Tank"));
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}