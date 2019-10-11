// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin play called!")); //Debug Log

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) //Crash Protection (Pointer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has possessed Actor: %s"), *GetName(), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullpointer on PlayerController - No Controlled Tank"));
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); ///IVAN NOTE: Cast is used here, to convert the return from 'GetPawn()', which is a APawn, into a ATank (the custom class). This is needed since we've specified the function return value as 'ATank'.
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank == nullptr) { return; }

	//Linetrace to vector in world code here.

	return;
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	//AimTowardsCrosshair();


}



