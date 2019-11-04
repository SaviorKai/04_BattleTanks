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
class UTankTrack;

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
	// Return current health as a percentage.
	UFUNCTION(BlueprintPure, Category = "Health")		// BlueprintPure = makes this a read only function in the blueprint (like const for c++)
		float GetHealthPercent();

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //TODO: What was this used for? 

protected:			
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/* // OLD CODE //
	UPROPERTY(BlueprintReadOnly) ///NOTE: This is moved here to protected, and as 'BlueprintReadOnly', since its called in the UI for 'MyFiringStatus' /// IVAN NOTE: If you don't set this as BlueprintReadOnly, you won't be able to drag the component into the blueprint. 
		UTankAimingComponent* TankAimingComponent = nullptr;
	*/

private:
	ATank();

	UPROPERTY(VisibleAnywhere)
		UTankTrack* LeftTankTrack = nullptr;                  /// TODO: Why is this visible on the tank properties at runtime? (It shows none). Think of fixing this.

	UPROPERTY(VisibleAnywhere)
		UTankTrack* RightTankTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Tank Setup")
		int32 StartingHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Tank Setup")
		int32 MyHealth = StartingHealth;

	// Called by the Engine when Actor Damage is dealt.
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
