// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Engine/World.h"

//Supporting the Forward Declarations
#include "TankBarrel.h" 
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;    //IVAN NOTE: We set this to false to improve performance! We don't need tick here.

	// Set the value of TankAimingComponent by creating a sub-object and adding it to the actor.
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::AimAt(FVector TargetLocation)
{
	TankAimingComponent->TurnAndAimAt(TargetLocation, LaunchSpeed);  /// NOTE: No need to protect pointer as its added in construction.
}

void ATank::SetBarrelReference(UTankBarrel* TankBarrel)  //NOTE!! THIS IS CALLED IN THE BLUEPRINT ON SPAWN TO SET THE VALUE!!!
{
	//Call the function on the Aiming component to pass down the set Barrel Reference.
	TankAimingComponent->SetBarrelReferenceAimComponent(TankBarrel);
	
	//Set the local Var on Tank
	MyBarrel = TankBarrel;
}

void ATank::SetTurretReference(UTankTurret* TankTurret)  //NOTE!! THIS IS CALLED IN THE BLUEPRINT ON SPAWN TO SET THE VALUE!!!
{
	TankAimingComponent->SetTurretReferenceAimComponent(TankTurret);
}

void ATank::Fire()
{
	//Check if ready to fire, by seeing how many seconds have passed since the last shot. This is better than setting the value to 0 manually.
	bool bIsReloaded = (FPlatformTime::Seconds() - LastShotTime) > ReloadTimeInSeconds;

	if (MyBarrel != nullptr)//Pointer Protection
	{
		if (bIsReloaded) //If you are ready to fire
		{
			//Spawn the Projectile       
			auto* MyProjectile = GetWorld()->SpawnActor<AProjectile>(                      // SpawnActor<CLASSTYPE>(CLASS,LOCATION,ROTATION)
				TankProjectileType,
				MyBarrel->GetSocketLocation(FName("ProjectileSpawn")),
				MyBarrel->GetSocketRotation(FName("ProjectileSpawn"))
				);

			MyProjectile->LaunchProjectile(LaunchSpeed);
			LastShotTime = FPlatformTime::Seconds();
		}
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

