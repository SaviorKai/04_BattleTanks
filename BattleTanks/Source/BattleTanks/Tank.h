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

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	///Methods
	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)					/// Creates this method as a item which can be called in Blueprints.
		void SetBarrelReference(UTankBarrel* TankBarrel);

	UFUNCTION(BlueprintCallable, Category = Setup)					/// Creates this method as a item which can be called in Blueprints.
		void SetTurretReference(UTankTurret* TankTurret);

protected:			// IVAN NOTE: Protected isn't public nor private.
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Create a class instance var *pointer of type UTankAimingComponent, and initialize it to nullptr.
	UTankAimingComponent* TankAimingComponent = nullptr;


private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000; // Sensible default starting vallue. 

};
