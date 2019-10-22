// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


///IVAN NOTE: This line below, just above UCLASS, is how you add comments which is seen in the editor to this item in the "Add component" list.

//This Component holds the Barrel properties and Elevate() method.     
UCLASS( ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward speed, and +1 is max upward speed
	void Elevate(float ElevatePosition);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 20.0f; //Sensible default.

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesElevation = 40.0f; //Sensible default.

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinDegreesElevation = 0.0f; //Sensible default.
	
};
