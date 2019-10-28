// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"   
#include "TankMovementComponent.h" // NOTE: Depends on TankMovementComponent for the pathfinding system via 'MoveToActor()' UE4 function

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//Log out Debug Messages
	//UE_LOG(LogTemp, Warning, TEXT("%s has possessed Actor: %s"), *GetName(), *ControlledTank->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("%s has Targeted: %s"), *GetName(), *PlayerTank->GetName());

	
	
}

///Runs Every Frame or Step of the game, Ticking continuously.
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  ///Super is just a line to tell the compiler to do what its SuperClass does (the mother of the class)
	
	//Use Cast to change the value of GetPawn which returns AActor, to ATank, and set the var pointers.
	auto MyTank = Cast<ATank>(GetPawn());     //TODO: How does this work without a * after auto? How does it become a pointer var type?
	auto EnemyTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(MyTank != nullptr))  //NULLPTR Protection
	{
		if (ensure(EnemyTank != nullptr)) //NULLPTR Protection
		{
			//Move Towards the player
			MoveToActor(EnemyTank, AcceptanceRadius);   /// NOTE: This is a UE4 Engine Function. We intercept it on the TankMovementComponent.
						
			//Call the public method on the Tank.cpp Class instance.
			MyTank->AimAt(EnemyTank->GetActorLocation());

			//Fire When Ready
			MyTank->Fire();  //TODO: Limit firing rate

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NULLPTR on TankAIController.EnemyTank!"));		// Can be removed, since we are using 'ensure'.
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULLPTR on TankAIController.MyTank!"));				// Can be removed, since we are using 'ensure'.
	}
	
	
}

///////// REFACTORED OUT - OLD CODE BELOW /////////
/*
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
*/