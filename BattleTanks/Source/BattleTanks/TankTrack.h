// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

//Must be last Include
#include "TankTrack.generated.h"

/**
* Tank Track is used to control the speed of the tank by setting the speed of each track individually.
* !!IVAN NOTE: Reminder that the Tank Track uses a Physics Material. Also remember that the linear dampening on the tank track, should be 0. Both of these need to be reset when a new track is added.
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
		float TrackMaxDrivingForce = 40000000.0;  //Assume 10mp/s (1g accelleration)

private: 
	UTankTrack();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
