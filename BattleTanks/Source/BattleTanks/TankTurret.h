// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"



UCLASS(ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downward speed, and +1 is max upward speed
	void RotateTurret(float RotationPosition);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxRotationPerSecond = 25.0; //Sensible default.

};
