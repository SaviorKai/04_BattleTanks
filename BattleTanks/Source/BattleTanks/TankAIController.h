// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

//Needs to be final include
#include "TankAIController.generated.h"

//Forward Declaration: 
class ATank;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// How close will the AI tank go towards target before stopping.
	float AcceptanceRadius = 2500;
};
