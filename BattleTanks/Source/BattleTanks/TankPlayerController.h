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
	virtual void BeginPlay() override;				/// Called when the game starts or when spwned (Ivan added)
	virtual void Tick(float DeltaTime) override;	/// Called every tick/step of the game (Ivan added)

	///Methods:
	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	//Out Param Method, true if hit something
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	

};
