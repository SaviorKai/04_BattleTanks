// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//#include "Engine.h"

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
		//UE_LOG(LogTemp, Warning, TEXT("Look direction %s"), *HitLocation.ToString());
	}
	
	///Aim Tank to the pointed position
	
	

	return;
}

//Out Param Method, true if hit something via a linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX
	int32 ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); ///Out paramater
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); ///IVAN NOTE: Yes, int32 can be multiplied by floats!
	
	// "De-Project the screen position of the crosshair to a world direction.
	// Line trace through this look direction and see what we hit (up to max range).


	OutHitLocation = FVector(1.0);
	return true;
}



///Runs Every Frame or Step of the game, Ticking continuously.
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	AimTowardsCrosshair();


}



