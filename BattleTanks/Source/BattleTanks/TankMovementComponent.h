// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"

//Always has to be the last include!
#include "TankMovementComponent.generated.h"

//Forward Declarations
class UTankTrack;




/**  TODO: Add these Class Titles for all my classes
 * 
 */

UCLASS( ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	///Fly-by-wire Controls
	UFUNCTION(BlueprintCallable, Category = "TankSetup") //This function manages the forward and backward movement of the tank.
		void IntendMoveForward(float Amount);

	UFUNCTION(BlueprintCallable, Category = "TankSetup") //This function manages the turning of the tank (Left and Right).
		void IntendTurnRight(float Amount);

	///Setup
	UFUNCTION(BlueprintCallable, Category = "TankSetup")
		void InitialiseMoveComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack);


private:
	UTankTrack* MyLeftTrack = nullptr;		//Set with the InitialiseMoveComponent() method.
	UTankTrack* MyRightTrack = nullptr;		//Set with the InitialiseMoveComponent() method.

	// Override Function which is called from the MoveToActor() UE4 Function, to intercept it. MoveToActor() is called in the TankAIContrroller.cpp
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;  /// Polymorphism (Sub-Type)
};
