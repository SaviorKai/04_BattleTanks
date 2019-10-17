// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

///Must Be the last Include
#include "TankPlayerController.generated.h"

//Forward Declaration
class ATank;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;				/// Called when the game starts or when spwned (Ivan added)
	virtual void Tick(float DeltaTime) override;	/// Called every tick/step of the game (Ivan added)

private:
	///Member Vars
	UPROPERTY(EditAnywhere)
		float CrossHairLocationX = 0.5;
	UPROPERTY(EditAnywhere)
		float CrossHairLocationY = 0.33333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0;


	///Methods:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();

	///Helper Methods
	bool GetSightRayHitLocation(FVector& OutHitLocation) const; //Out Param Method, true if hit something
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const; //Out Param Method
	bool GetLookVectorHitLocation(FVector CamLookDirection, FVector& HitLocationPoint) const;

};
