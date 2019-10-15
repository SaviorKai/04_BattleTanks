// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

//Needs to be final include
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	///Methods:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	///Member Vars
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;


};
