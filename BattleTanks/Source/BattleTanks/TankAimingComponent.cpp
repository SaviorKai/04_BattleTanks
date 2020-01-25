// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h" //Supporting the Forward Declaration
#include "TankTurret.h" //Supporting the Forward Declaration
#include "Projectile.h" //Supporting the Forward Declaration
#include "DrawDebugHelpers.h"

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
	if (MyAmmoCount <= 0)
	{
		MyFiringState = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastShotTime) < ReloadTimeInSeconds)
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

	//auto StartLocation = MyTankBarrel->GetSocketLocation(FName("ProjectileSpawn"));
	auto StartLocation = MyTankTurret->GetComponentLocation();

	FVector TossVelocity(0); //Make sure you initialize vectors. //OUT PARAM

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,			// World context object. Grabs the class we're currently in. In this case, TankAimingComponent.cpp.
		OUT TossVelocity,
		StartLocation,
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

		// DEBUG
		/*
		if (Cast<APawn>(GetOwner())->IsPlayerControlled())
		{
			auto TempCompLocation = MyTankBarrel->GetComponentLocation();
			auto TempForwardLocation = MyTankBarrel->GetSocketLocation(FName("ProjectileSpawn"));
			auto TempDifference = (TempForwardLocation - TempCompLocation);
			auto TempTargetLocation = (TempDifference * 10) + TempCompLocation;
			
			DrawDebugSphere(GetWorld(), TempCompLocation, 50, 32, FColor::Red, false, 0, 0, 1.0f);
			DrawDebugSphere(GetWorld(), TempTargetLocation, 50, 32, FColor::Blue, false, 0, 0, 1.0f);

			DrawDebugLine(GetWorld(), TempCompLocation, TempTargetLocation, FColor::Green, false, 0, 0, 5); 
		}
		*/ // DEBUG END
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
		if (MyFiringState == EFiringStatus::Aiming || MyFiringState == EFiringStatus::Locked)
		{
			//Spawn the Projectile       
			auto* MyProjectile = GetWorld()->SpawnActor<AProjectile>(						// SpawnActor<CLASSTYPE>(CLASS,LOCATION,ROTATION)
				TankProjectileType,															// TankProjectileType is a var we've created in the headerfile.
				MyTankBarrel->GetSocketLocation(FName("ProjectileSpawn")),
				MyTankBarrel->GetSocketRotation(FName("ProjectileSpawn"))
				);

			//Move the Projectile
			if (ensure(MyProjectile)) ///Pointer protection incase the projectile doesn't spawn.
			{
				MyProjectile->LaunchProjectile(LaunchSpeed);
			}
			LastShotTime = GetWorld()->GetTimeSeconds();
			MyAmmoCount -= 1;
		}
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(MyTankBarrel != nullptr)) { return; } // NULLPTR protection.

	//Work out the difference between the two points
	auto CurrentBarrelRotation = MyTankBarrel->GetForwardVector().Rotation();
	auto TargetRotation = AimDirection.Rotation();
	auto RoationDifference = TargetRotation - CurrentBarrelRotation;
	
	//Move the Barrel
	MyTankBarrel->Elevate(RoationDifference.Pitch);

	//UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation: %s , AimAsRotator is %s"), *BarrelRotation.ToString(), *AimAsRotator.ToString());
}

void UTankAimingComponent::MoveTurret(FVector AimDirection) //// TODO: Combine this method with the Move Barrel Method. It can be combined.
{
	if (!ensure(MyTankTurret != nullptr)) { return; } // NULLPTR protection.
	
	//Calculate the difference between the two  points
	auto CurrentTurretRotation = MyTankTurret->GetForwardVector().Rotation();
	auto TargetRotation = AimDirection.Rotation();
	auto RoationDifference = TargetRotation - CurrentTurretRotation;

	float FixedRotationDifference = 0; //Used for Ivan Solution
	
	// LECTURE SOLUTION 
	if (FMath::Abs(RoationDifference.Yaw) < 180) // if Positive value
	{
		MyTankTurret->RotateTurret(RoationDifference.Yaw);
	}
	else
	{
		MyTankTurret->RotateTurret(-RoationDifference.Yaw);
	}
	
	/*
	/// IVAN SOLUTION - Working.

	/// Turn the shortest way only.
	if (RoationDifference.Yaw > 180) // if Positive value
	{
		FixedRotationDifference = RoationDifference.Yaw - 360;
	}
	else if (RoationDifference.Yaw < -180) // if Negative value
	{
		FixedRotationDifference = RoationDifference.Yaw + 360;
	}
	else // if Exactly = 0 (just to avoid bugs)
	{
		FixedRotationDifference = RoationDifference.Yaw;
	}

	//Move the Turret
	MyTankTurret->RotateTurret(FixedRotationDifference);
	*/
}

bool UTankAimingComponent::IsBarrelMoving()
{
	///Pointer Protection
	if (!ensure(MyTankBarrel != nullptr)) { return false; } // NULLPTR protection.

	auto BarrelForward = MyTankBarrel->GetForwardVector();

	return (!BarrelForward.Equals(CurrentAimDirection, 0.1f));
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return MyFiringState;
}
