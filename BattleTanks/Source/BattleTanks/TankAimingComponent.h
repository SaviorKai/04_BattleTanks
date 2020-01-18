// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

///Needs to be the last include
#include "TankAimingComponent.generated.h"

// EFiring Status Enum class creation.
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

//Forward Declaration: 
class UTankBarrel;
class UTankTurret;
class AProjectile;

/// IVAN NOTE: This line below, just above UCLASS, is how you add comments which is seen in the editor to this item in the "Add component" list.

//This Aiming component Sets the reference of the barrel for the tank and holds the TurnAndAimAt() method to get SuggestProjectileVelocity().
UCLASS( ClassGroup = (TankParts), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent(); 
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	///Methods
	void TurnAndAimAt(FVector TargetLocation);
	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category="Setup")
		void InitialiseAimComponent(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

	UFUNCTION(BlueprintCallable, Category = "TankSetup") /// Made this a Blueprint callable function since we want to call it via input in blueprints.
		void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Setup Ammo Count
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firing") /// TODO: Note: In the lecture, we are told to use a getter method to find this value, instead of setting them up as blueprintreadonly. Perhaps the same can be done for the Firing State.
		int32 MyAmmoCount = 20;											/// TODO: Test all the different types of things you can do (EditDefaultsOnly, BlueprintReadOnly) in protected, private, public, and also none used. Do the same for UFUNCTION.

	// Setup MyFiringStatus enum var, which can be called by the UI.  
	UPROPERTY(BlueprintReadOnly, Category = "Setup") /// Why protected:? Remember that the parent of bp_TankAimingComponent is the C++ class TankAimingComponent.cpp. Thus, this needs to be in protected, so that the child classes can call it. 
		EFiringStatus MyFiringState = EFiringStatus::Reloading;

private:
	UTankBarrel* MyTankBarrel = nullptr;
	UTankTurret* MyTankTurret = nullptr;
	FVector CurrentAimDirection = FVector(0,0,0);
	float LastShotTime = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000; // Sensible default starting vallue.
	
	UPROPERTY(EditAnywhere, Category = "Firing")  /// IVAN NOTE: EditAnywhere, means it can be changed on the default, and on the instances during runtime. EditDefaultsOnly, means you can only edit the default in the editor (not the instances).
		float ReloadTimeInSeconds = 3; // Sensible default starting vallue.
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> TankProjectileType;	//Method 1: In this method, I can be specific about which subclasses to include.
		//UClass* TankProjectileType;					//Method 2: All classes to choose from in the dropdown. Here I am setting the TYPES of classes you can choose from (UClass = All), and then giving it a name as a var (TankProjectileType), which is then referecenced in the Editor. This one is dangerous, as if you choose the wrong one, the editor will crash.

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
	bool IsBarrelMoving();

};
