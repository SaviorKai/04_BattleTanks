// All rights reserved © 2019 Ivan Carl Engelbrecht

// TODO: go through entire Tanks game, Tripple X game, and Bulls & cows, and document all C++ items.
// TODO: go through this, test and understand https://godbolt.org/z/h2QPhc
// TODO: Clean up all code and format them the same.
// TODO: Revisit NavMesh and Navigation.
// TODO: redo the lighting

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations: 
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrack;
class UParticleSystemComponent;
class UAudioComponent;

// Declare Delegate
///[DMCD Step 1] Create delegate type
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Return current health as a percentage.
	UFUNCTION(BlueprintPure, Category = "Health")		// BlueprintPure = makes this a read only function in the blueprint (like const for c++)
		float GetHealthPercent();

	UFUNCTION(BlueprintPure, Category = "Health")		// BlueprintPure = makes this a read only function in the blueprint (like const for c++)
		float GetScore();

	UFUNCTION(BlueprintPure, Category = "Health")		// BlueprintPure = makes this a read only function in the blueprint (like const for c++)
		bool HasDied();

	///[DMCD Step 2] Declare delegate.
	FTankDelegate OnDeath;

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //TODO: What was this used for? 

	void CounterSliding();
	void PlayEngineMoveSound();
	void StopEngineMoveSound();

protected:			
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent) // NOTE: We don't define BlueprintImplementableEvent in C++ (it's done in blueprint)
	void PlayDeathFx();

	void AddScore(int32 Amount);
	
	/* // OLD CODE //
	UPROPERTY(BlueprintReadOnly) ///NOTE: This is moved here to protected, and as 'BlueprintReadOnly', since its called in the UI for 'MyFiringStatus' /// IVAN NOTE: If you don't set this as BlueprintReadOnly, you won't be able to drag the component into the blueprint. 
		UTankAimingComponent* TankAimingComponent = nullptr;
	*/

private:
	ATank();

	bool bHasDied = false;

	UPROPERTY(VisibleAnywhere)
		UTankTrack* LeftTankTrack = nullptr;                  /// TODO: Why is this visible on the tank properties at runtime? (It shows none). Think of fixing this.

	UPROPERTY(VisibleAnywhere)
		UTankTrack* RightTankTrack = nullptr;
	
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* DeathSmokeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Tank Setup")
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Tank Setup")
		int32 MyHealth = 0;  //Set at Beginplay(). If this was set here, the blueprint value won't get picked up, and be the default 100. 

	// Called by the Engine when Actor Damage is dealt.
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundBase* Sound_EngineIdle = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundBase* Sound_EngineMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USoundBase* Sound_TankDeathFlames = nullptr;

	UAudioComponent* MyEngine_IdleSound = nullptr;
	UAudioComponent* MyEngine_MovingSound = nullptr;

	int32 MyScore = 0;

	FTimerHandle Timer_DestroyMe;
	void DestroyMe();

};
