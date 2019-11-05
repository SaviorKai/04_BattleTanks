// All rights reserved © 2019 Ivan Carl Engelbrecht

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
