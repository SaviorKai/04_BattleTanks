// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

///Must Be the last Include
#include "Tank.generated.h"

//Forward Declarations: 
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

/* IVAN NOTE ABOUT public, protected, private:
// public: You can access it anywhere.
// protected: This class and its inheretance can call these.
// private: Only I can call these.
//
// It's important to remember, that if we create a BluePrint class from our C++ classes, the BLUEPRINT class is still a child of the main C++ class.
*/

public:
	// Sets default values for this pawn's properties
	ATank();

	///Methods
	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "TankSetup") /// Made this a Blueprint callable function since we want to call it via input in blueprints.
		void Fire();



protected:			/// IVAN NOTE: Protected isn't public nor private.
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	/* ============= OLD - NOT USED ANYMORE =============
	//Declare a var that can be called from the Blueprint, to hold the movement component, so that we can target it. /// IVAN NOTE: If you don't set this as BlueprintReadOnly, you won't be able to drag the component into the blueprint. 
	UPROPERTY(BlueprintReadOnly) 
		UTankMovementComponent* TankMovementComponent = nullptr;
	*/
	UPROPERTY(BlueprintReadOnly) ///NOTE: This is moved here to protected, as 'BlueprintReadOnly', since its called in the UI for 'MyFiringStatus'
		UTankAimingComponent* TankAimingComponent = nullptr;
	

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //TODO: This could be removed? 

	UFUNCTION(BlueprintCallable, Category = "TankSetup")					/// Creates this method as a item which can be called in Blueprints.
		void SetupComponents(UTankAimingComponent* AimingComponent, UTankBarrel* TankBarrel);

	//Private Vars
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; // Sensible default starting vallue. 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		//UClass* TankProjectileType;					//Method 1: All classes to choose from in the dropdown. Here I am setting the TYPES of classes you can choose from (UClass = All), and then giving it a name as a var (TankProjectileType), which is then referecenced in the Editor. This one is dangerous, as if you choose the wrong one, the editor will crash.
		TSubclassOf<AProjectile> TankProjectileType;	//Method 2: In this method, I can be specific about which subclasses to include.

	UPROPERTY(EditAnywhere, Category = "Firing")  /// IVAN NOTE: EditAnywhere, means it can be changed on the default, and on the instances during runtime. EditDefaultsOnly, means you can only edit the default in the editor (not the instances).
		float ReloadTimeInSeconds = 3; // Sensible default starting vallue.

	UTankBarrel* MyBarrel = nullptr; //My Barrel (Local Reference for spawning projectile)

	float LastShotTime = 0; 
};
