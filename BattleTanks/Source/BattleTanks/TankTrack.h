// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

//Must be last Include
#include "TankTrack.generated.h"

/**
* Tank Track is used to control the speed of the tank by setting the speed of each track individually.
* [!]NOTES: The following must be set when adding a new track to a tank:
*	- Reminder that the Tank Track uses a Physics Material, make sure you add it.
*	- Also remember that the linear dampening on the tank track, should be 0. 
*	- Lastly, Ensure "Generate Event Hit Events" is turned on. 
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
	virtual void BeginPlay() override;

	void ApplySidewaysForce();
	void DriveTrack();

	float Throttle;
	


	//2. Use this signature for the delegate (OnHit())
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
