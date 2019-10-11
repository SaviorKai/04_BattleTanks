// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Tank.h"

///Must Be the last Include
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	// Called when the game starts or when spwned (Ivan added)
	virtual void BeginPlay() override;

	///Methods:
	ATank* GetControlledTank() const;

};
