// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

///Needs to be the last include
#include "TankAimingComponent.generated.h"

//Forward Declaration: 
class UTankBarrel;


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

private:
	UTankBarrel* MyTankBarrel = nullptr;
	
	void MoveBarrel(FVector AimDirection);
		
};
