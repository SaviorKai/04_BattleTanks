// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include "Tank.h" //Supporting forward declaration.

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin play called!")); //Debug Log

	auto ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) //Crash Protection (Pointer)
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
		///Aim Tank to the pointed position
		GetControlledTank()->AimAt(HitLocation); //Call the public method on the Tank.cpp Class instance.
	}
	
	return;
}


//Out Param Method, true if hit something via a linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); ///Out paramater
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); ///IVAN NOTE: Yes, int32 can be multiplied by floats!
	
	// "De-Project" the screen position of the crosshair to a world direction.
	FVector CamLookDirection;
	if (GetLookDirection(ScreenLocation, OUT CamLookDirection))
	{
		// Line trace through this look direction and see what we hit (up to max range).
		GetLookVectorHitLocation(CamLookDirection, OutHitLocation);   
	}
		
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded, but needed for the Deproject function.
	
	return DeprojectScreenPositionToWorld(						///Ivan Note: This is a out paramater BOOL function, which means it can be used as a If statement.
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OUT LookDirection
	);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector CamLookDirection, FVector& HitLocationPoint) const
{
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + (CamLookDirection * LineTraceRange);		 //IVAN NOTE: '(FRotator.FVector() * Length)' is similar to the LengthDir function
	
	///DEBUG DRAW LINE
	/*
	DrawDebugLine(
		GetWorld(),
		LineTraceStart,
		LineTraceEnd,
		FColor::Red,
		false,
		-1,
		1,
		10.0
	);
	*/
	
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult, LineTraceStart, 
		LineTraceEnd, 
		ECollisionChannel::ECC_Visibility
		))
	{
		HitLocationPoint = HitResult.Location;
		return true;
	}
	
	return false;
}


///Runs Every Frame or Step of the game, Ticking continuously.
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	AimTowardsCrosshair();


}



