// All rights reserved � 2019 Ivan Carl Engelbrecht //TODO for all classes

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"
#include "Tank.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Call the FoundAimingComponent Event and let it run.
	if (!GetPawn()) { return; }															// NULLPTR Protection
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();		// IVAN NOTE! Used FINDcomponentByClass, not GET. !! This doesn't exist in blueprints.
	if (!ensure(AimingComponent != nullptr)) { return; }								// NULLPTR Protection.
	
	FoundAimingComponent(AimingComponent);
}



///Runs Every Frame or Step of the game, Ticking continuously.
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	AimTowardsCrosshair();

}

float ATankPlayerController::GetMyScore()
{
	return MyPlayerScore;
}

/* //OLD CODE 
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); /// IVAN NOTE: Cast is used here, to convert the return from 'GetPawn()', which is a APawn, into a ATank (the custom class). This is needed since we've specified the function return value as 'ATank'.
}
*/

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetPawn() == nullptr) { return; } /// NULLPTR Protection: Check if we have a tank we're controlling before doing anything.

	FVector HitLocation; //OUT Parameter
	bool bGotHitLocation = GetSightRayHitLocation(OUT HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation = %i"), bGotHitLocation);
	if (bGotHitLocation)
	{
		///Aim Tank to the pointed position
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();  /// IVAN NOTE! Used FINDcomponentByClass, not GET. !! This doesn't exist in blueprints.
		if (AimingComponent == nullptr) { return; }  /// NULLPTR Protection.

		AimingComponent->TurnAndAimAt(HitLocation);
	}
}


//Out Param Method, true if hit something via a linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); ///Out paramater
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY); /// IVAN NOTE: Yes, int32 can be multiplied by floats! But not always a good idea.

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

	FCollisionQueryParams QueryParams;
	if (GetPawn())
	{
		QueryParams.AddIgnoredActor(GetPawn());
	}

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult, 
		LineTraceStart,
		LineTraceEnd,
		ECollisionChannel::ECC_Camera,				//Set to CAMERA, so that we don't clash with UI objects.
		QueryParams
	))
	{
		HitLocationPoint = HitResult.Location;
		
		return true;
	}

	return false;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn); // Remember to call SUPER! 
	
	if (InPawn)  //Pointer Protection
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; } //PointerProtection

		///[DMCD Step 5] Register the event and pass the function we've created to take action.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);   //This tells the possessed tank, to let us know when the OnDeath() event is triggered, let us know and trugger OnPossessedTankDeath() here.
	}
}

void ATankPlayerController::OnPossesedTankDeath()
{
	MyPlayerScore = Cast<ATank>(GetPawn())->GetScore();
	StartSpectatingOnly();			//Turns the player to a spectator on death.
}
