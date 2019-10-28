// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

///Must Be the last Include
#include "Tank.generated.h"

//Forward Declarations: 
class UTankBarrel;
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
	UFUNCTION(BlueprintCallable, Category = "TankSetup") /// Made this a Blueprint callable function since we want to call it via input in blueprints.
		void Fire(); ///TODO: Complete move to Aiming Component (and update input blueprint to call this accurately.

protected:			
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/* // OLD CODE //
	UPROPERTY(BlueprintReadOnly) ///NOTE: This is moved here to protected, and as 'BlueprintReadOnly', since its called in the UI for 'MyFiringStatus' /// IVAN NOTE: If you don't set this as BlueprintReadOnly, you won't be able to drag the component into the blueprint. 
		UTankAimingComponent* TankAimingComponent = nullptr;
	*/

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //TODO: This could be removed? 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> TankProjectileType;	//Method 1: In this method, I can be specific about which subclasses to include.
		//UClass* TankProjectileType;					//Method 2: All classes to choose from in the dropdown. Here I am setting the TYPES of classes you can choose from (UClass = All), and then giving it a name as a var (TankProjectileType), which is then referecenced in the Editor. This one is dangerous, as if you choose the wrong one, the editor will crash.

	UPROPERTY(EditAnywhere, Category = "Firing")  /// IVAN NOTE: EditAnywhere, means it can be changed on the default, and on the instances during runtime. EditDefaultsOnly, means you can only edit the default in the editor (not the instances).
		float ReloadTimeInSeconds = 3; // Sensible default starting vallue.

	float LastShotTime = 0; 
};
