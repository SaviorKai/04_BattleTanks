// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

//Must be last Include
#include "TankTrack.generated.h"

/**
* Tank Track is used to control the speed of the tank by setting the speed of each track individually.
*/

UCLASS(ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent)) /// Makes the Class spawnnable in blueprints
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/// Public Methods
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float Amount);

	/// Public Varibles
	//Max force per track, in Newtons.
	UPROPERTY(EditDefaultsOnly, Category = "TrackSetup")
		float TrackMaxDrivingForce = 400000.00;  //Assume 10mp/s (1g accelleration)
};
