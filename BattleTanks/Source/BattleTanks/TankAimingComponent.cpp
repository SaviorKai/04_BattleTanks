// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h" //Supporting the Forward Declaration
#include "TankTurret.h" //Supporting the Forward Declaration

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO: Should this tick?

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::TurnAndAimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (MyTankBarrel == nullptr) { return; } //Pointer Protection

	
	FVector TossVelocity(0); //Make sure you initialize vectors.

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,			// World context object. Grabs the class we're currently in. In this case, TankAimingComponent.cpp.
		OUT TossVelocity,
		MyTankBarrel->GetSocketLocation(FName("ProjectileSpawn")),
		TargetLocation,
		LaunchSpeed,
		false,      
		0,			
		0,			
		ESuggestProjVelocityTraceOption::DoNotTrace      //NOTE! This argument is required for this function to work!
	);

	if (bHaveAimSolution) 
	{
		//Normalize the value of TossVelocity to a combined directional value of 1 with GetSafeNormal().
		FVector AimDirection = TossVelocity.GetSafeNormal();

		//DEBUGLOGS: 
		UE_LOG(LogTemp, Warning, TEXT("Aim Solution: %s"), *TossVelocity.ToString());

		///Move the barrel to aim at the solution location. 
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IMPOSSIBLE TossVelocity!!"));
	}
	



	///DEBUG LOGS
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s. Barrel Posision is: %s"), *GetOwner()->GetName(), *TargetLocation.ToString(), *MyTankBarrel->GetComponentLocation().ToString());
}

void UTankAimingComponent::SetBarrelReferenceAimComponent(UTankBarrel* TankBarrel)
{
	//Set the var to the instance id of the Barrel Component of the tank.
	MyTankBarrel = TankBarrel;

	if (MyTankBarrel == nullptr) //PointerProtection.
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr on SetBarrelReferenceAimComponent()"));
		return;
	}
}

void UTankAimingComponent::SetTurretReferenceAimComponent(UTankTurret* TankTurret)
{
	//Set the var to the instance id of the Turret Component of the tank.
	MyTankTurret = TankTurret;

	if (MyTankTurret == nullptr) //PointerProtection.
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr on SetTurretReferenceAimComponent()"));
		return;
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (MyTankBarrel == nullptr) { return; } //Pointer protection.

	//Work out the difference between the two points
	FRotator CurrentBarrelRotation = MyTankBarrel->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator RoationDifference = TargetRotation - CurrentBarrelRotation;
	
	//Move the Barrel
	MyTankBarrel->Elevate(RoationDifference.Pitch);

	//UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation: %s , AimAsRotator is %s"), *BarrelRotation.ToString(), *AimAsRotator.ToString());
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	if (MyTankTurret == nullptr) { return; } //Pointer protection.
	
	//Calculate the difference between the two  points
	FRotator CurrentTurretRotation = MyTankTurret->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator RoationDifference = TargetRotation - CurrentTurretRotation;

	//Move the Turret
	MyTankTurret->RotateTurret(RoationDifference.Yaw);

}

