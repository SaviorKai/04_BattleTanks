// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

//Needs to be final include
#include "TankAIController.generated.h"

//Forward Declaration: 
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// How close will the AI tank go towards target before stopping.
	UPROPERTY(EditDefaultsOnly, Category = "Tank Setup")  //TODO: Why does this work, without it being protected? Because it's not bluieprint callable. If it was blueprint callable, it wouldn't work.
		float AcceptanceRadius = 3000;
	
	/// This Function is called by the engine AIController class, when it posseses a pawn. We intercept it. 
	virtual void SetPawn(APawn* InPawn) override;

	///[DMCD Step 4] Declare Delegate Listener (method to execute when delegate is called)
	UFUNCTION()
		void OnPossessedTankDeath(); /// Delegate Method.
};
