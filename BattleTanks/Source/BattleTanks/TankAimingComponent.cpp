// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TankBarrel.h" //Supporting the Forward Declaration
#include "TankTurret.h" //Supporting the Forward Declaration
#include "Projectile.h" //Supporting the Forward Declaration

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	//Check if ready to fire, by seeing how many seconds have passed since the last shot. This is better than setting the value to 0 manually.
	if ((GetWorld()->GetTimeSeconds() - LastShotTime) < ReloadTimeInSeconds)
	{
		MyFiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		MyFiringState = EFiringStatus::Aiming;
	}
	else
	{
		MyFiringState = EFiringStatus::Locked;
	}
}


void UTankAimingComponent::TurnAndAimAt(FVector TargetLocation)
{
	if (!ensure(MyTankBarrel != nullptr)) { return; }	 //NULLPTR Protection   

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
		ESuggestProjVelocityTraceOption::DoNotTrace      /// IVAN NOTE! This argument is required for this function to work!
	);

	if (bHaveAimSolution)
	{
		//Normalize the value of TossVelocity to a combined directional value of 1 with GetSafeNormal().
		FVector AimDirection = TossVelocity.GetSafeNormal();

		//DEBUGLOGS: 
		//UE_LOG(LogTemp, Warning, TEXT("Aim Solution: %s"), *TossVelocity.ToString());

		///Move the barrel to aim at the solution location. 
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);

		///Set the Private Var for use in other checks
		CurrentAimDirection = AimDirection;
	}
	else
	{
		///NoAimSolution Found.
		//UE_LOG(LogTemp, Warning, TEXT("%f: IMPOSSIBLE TossVelocity!!"), GetWorld()->GetTimeSeconds());
	}

	///DEBUG LOGS
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s. Barrel Posision is: %s"), *GetOwner()->GetName(), *TargetLocation.ToString(), *MyTankBarrel->GetComponentLocation().ToString());
}


void UTankAimingComponent::InitialiseAimComponent(UTankBarrel* TankBarrel, UTankTurret* TankTurret)
{
	MyTankBarrel = TankBarrel;
	MyTankTurret = TankTurret;
}

void UTankAimingComponent::Fire()
{
	if (ensure(MyTankBarrel != nullptr))	//NULLPTR Protection
	{
		//if (bIsReloaded) //If you are ready to fire
		if (MyFiringState != EFiringStatus::Reloading)
		{
			//Spawn the Projectile       
			auto* MyProjectile = GetWorld()->SpawnActor<AProjectile>(                      // SpawnActor<CLASSTYPE>(CLASS,LOCATION,ROTATION)
				TankProjectileType,
				MyTankBarrel->GetSocketLocation(FName("ProjectileSpawn")),
				MyTankBarrel->GetSocketRotation(FName("ProjectileSpawn"))
				);

			//Move the Projectile
			if (ensure(MyProjectile)) ///Pointer protection incase the projectile doesn't spawn.
			{
				MyProjectile->LaunchProjectile(LaunchSpeed);
			}
			LastShotTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(MyTankBarrel != nullptr)) { return; } // NULLPTR protection.

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
	if (!ensure(MyTankTurret != nullptr)) { return; } // NULLPTR protection.
	
	//Calculate the difference between the two  points
	FRotator CurrentTurretRotation = MyTankTurret->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator RoationDifference = TargetRotation - CurrentTurretRotation;

	//Move the Turret
	MyTankTurret->RotateTurret(RoationDifference.Yaw);

}

bool UTankAimingComponent::IsBarrelMoving()
{
	///Pointer Protection
	if (!ensure(MyTankBarrel != nullptr)) { return false; } // NULLPTR protection.

	auto BarrelForward = MyTankBarrel->GetForwardVector();

	return (!BarrelForward.Equals(CurrentAimDirection, 0.1f));
}

