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
	///Public Methods
	//Fly-by-wire Control Forward.
	UFUNCTION(BlueprintCallable, Category = TankSetup)
		void IntendMoveForward(float Amount);

	UFUNCTION(BlueprintCallable, Category = TankSetup)
		void InitialiseMoveComponent(UTankTrack* LeftTrack, UTankTrack* RightTrack);

private:
	UTankTrack* MyLeftTrack = nullptr;
	UTankTrack* MyRightTrack = nullptr;
};
