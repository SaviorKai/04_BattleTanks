// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

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
	if (GetControlledTank() == nullptr) { return; } ///Check if we have a tank we're controlling before doing anything.

	FVector HitLocation; //OUT Parameter
	if (GetSightRayHitLocation(OUT HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation %s"), *HitLocation.ToString());
	}
	
	///Aim Tank to the pointed position
	
	

	return;
}

//Out Param Method, true if hit something via a linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	
	///Linetrace out and see if we hit anything.
	OutHitLocation = FVector(1.0);
	
	//If the crosshair trace hits something
		//Set the out location to the point it hit
		//return true;
	//else
		//return false;

	
	return true;
	
	
	



}



///Runs Every Frame or Step of the game, Ticking continuously.
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	AimTowardsCrosshair();


}



