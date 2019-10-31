// Fill out your copyright notice in the Description page of Project Settings. //TODO for all classes

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Call the FoundAimingComponent Event and let it run.
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();  /// IVAN NOTE! Used FINDcomponentByClass, not GET. !! This doesn't exist in blueprints.
	if (!ensure(AimingComponent != nullptr)) { return; }  /// NULLPTR Protection.
	
	FoundAimingComponent(AimingComponent);
}



///Runs Every Frame or Step of the game, Ticking continuously.
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	AimTowardsCrosshair();

}

/* //OLD CODE 
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); /// IVAN NOTE: Cast is used here, to convert the return from 'GetPawn()', which is a APawn, into a ATank (the custom class). This is needed since we've specified the function return value as 'ATank'.
}
*/

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn() != nullptr)) { return; } /// NULLPTR Protection: Check if we have a tank we're controlling before doing anything.

	FVector HitLocation; //OUT Parameter
	bool bGotHitLocation = GetSightRayHitLocation(OUT HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation = %i"), bGotHitLocation);
	if (bGotHitLocation)
	{
		///Aim Tank to the pointed position
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();  /// IVAN NOTE! Used FINDcomponentByClass, not GET. !! This doesn't exist in blueprints.
		if (!ensure(AimingComponent != nullptr)) { return; }  /// NULLPTR Protection.

		AimingComponent->TurnAndAimAt(HitLocation);
	}
}


//Out Param Method, true if hit something via a linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); ///Out paramater
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); /// IVAN NOTE: Yes, int32 can be multiplied by floats!

	// "De-Project" the screen position of the crosshair to a world direction.
	FVector CamLookDirection;
	if (GetLookDirection(ScreenLocation, OUT CamLookDirection))
	{
		// Line trace through this look direction and see what we hit (up to max range).
		return GetLookVectorHitLocation(CamLookDirection, OutHitLocation);
	}

	return false; //This should always return false if it can't find a target to hit
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded, but needed for the Deproject function.

	return DeprojectScreenPositionToWorld(						/// IVAN NOTE: This is a out paramater BOOL function, which means it can be used as a If statement.
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OUT LookDirection
	);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector CamLookDirection, FVector& HitLocationPoint) const
{
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + (CamLookDirection * LineTraceRange);		 /// IVAN NOTE: '(FRotator.FVector() * Length)' is similar to the LengthDir function

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
