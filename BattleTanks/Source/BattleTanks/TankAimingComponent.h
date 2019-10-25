// Fill out your copyright notice in the Description page of Project Settings.

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
	Reloading
};

//Forward Declaration: 
class UTankBarrel;
class UTankTurret;

/// IVAN NOTE: This line below, just above UCLASS, is how you add comments which is seen in the editor to this item in the "Add component" list.

//This Aiming component Sets the reference of the barrel for the tank and holds the TurnAndAimAt() method to get SuggestProjectileVelocity().
UCLASS( ClassGroup = (TankParts), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent(); 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Setup MyFiringStatus enum var, which can be called by the UI. 
	UPROPERTY(BlueprintReadOnly, Category = "Setup") /// Why protected:? Remember that the parent of bp_TankAimingComponent is the C++ class TankAimingComponent.cpp. Thus, this needs to be in protected, so that the child classes can call it. 
		EFiringStatus MyFiringState = EFiringStatus::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	///Methods
	void TurnAndAimAt(FVector TargetLocation, float LaunchSpeed);
	
	UFUNCTION(BlueprintCallable, Category="Setup")
		void InitialiseAimComponent(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

private:
	UTankBarrel* MyTankBarrel = nullptr;
	UTankTurret* MyTankTurret = nullptr;
		
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
		
};
