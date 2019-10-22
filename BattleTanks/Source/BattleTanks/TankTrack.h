// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
* Tank Track is used to control the speed of the tank by setting the speed of each track individually.
*/

UCLASS( ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent) ) /// Makes the Class spawnnable in blueprints
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public: 
	UTankTrack(); ///Ivan added. Constructor.

	//Public Methods
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float Amount);
};
