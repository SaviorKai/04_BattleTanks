// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

///Needs to be the last include
#include "TankAimingComponent.generated.h"

//Forward Declaration: 
class UTankBarrel;
class UTankTurret;

///IVAN NOTE: This line below, just above UCLASS, is how you add comments which is seen in the editor to this item in the "Add component" list.

//This Aiming component Sets the reference of the barrel for the tank and holds the TurnAndAimAt() method to get SuggestProjectileVelocity().
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	///Methods
	void TurnAndAimAt(FVector TargetLocation, float LaunchSpeed);
	void SetBarrelReferenceAimComponent(UTankBarrel* TankBarrel);
	void SetTurretReferenceAimComponent(UTankTurret* TankTurret);

private:
	UTankBarrel* MyTankBarrel = nullptr;
	UTankTurret* MyTankTurret = nullptr;
	
	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
		
};
