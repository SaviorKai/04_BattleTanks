// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//Log out Debug Messages
	//UE_LOG(LogTemp, Warning, TEXT("%s has possessed Actor: %s"), *GetName(), *ControlledTank->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("%s has Targeted: %s"), *GetName(), *PlayerTank->GetName());
	
}

ATank* ATankAIController::GetControlledTank() const
{
	if (Cast<ATank>(GetPawn()) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr on TankAIController::GetControlledTank()!!"));
		return Cast<ATank>(GetPawn()); //IVAN NOTE: Cast is used here, to convert the return from 'GetPawn()', which is a APawn, into a ATank (the custom class). This is needed since we've specified the function return value as 'ATank'.
	}
	else
	{
		return Cast<ATank>(GetPawn());
	}
}

///Find Enemy Tank (The player) and target it.
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr on TankAIController::GetPlayerTank()"));
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerTank);
	}
	
}


///Runs Every Frame or Step of the game, Ticking continuously.
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	 
	//Pointer Protection and log.
	if (GetControlledTank() == nullptr) { return; }

	///Find the target tank (the player)
	if (GetPlayerTank() != nullptr) //Pointer Protection   (Logged in function def)
	{ 
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); //Call the public method on the Tank.cpp Class instance.
	}
	return;
	
	
}