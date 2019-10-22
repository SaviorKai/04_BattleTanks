// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

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
	
};
