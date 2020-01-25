// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

//Must be last Include
#include "TankTrack.generated.h"

class USphereComponent;

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
	float TrackMaxDrivingForce = 200000.0f;	//float TrackMaxDrivingForce = 40000000.0;  //Assume 10mp/s (1g accelleration)

private: 
	UTankTrack();
	virtual void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels() const;						// Create a function that returns an array of ASprungWheel Pointers. //TODO: Revisit Arrays, and also, is this like making a forward Declaration? Test it.

	void DriveTrack(float Throttle);

	void SetupMeshWheels();
	void RotateMeshWheels();

	USphereComponent* MyMainWheel = nullptr;
	TArray<UStaticMeshComponent*> MeshWheels;
};
