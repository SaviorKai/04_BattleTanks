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
	PrimaryActorTick.bCanEverTick = false;    /// IVAN NOTE: We set this to false to improve performance! We don't need tick here.

	/// SPAWN and SET the value of TankAimingComponent by creating a sub-object and adding it to the actor.

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

void ATank::AimAt(FVector TargetLocation)
{
	if (TankAimingComponent == nullptr) { return; } //Pointer Protection

	TankAimingComponent->TurnAndAimAt(TargetLocation, LaunchSpeed);  
}

void ATank::SetupComponents(UTankAimingComponent* AimingComponent, UTankBarrel* TankBarrel)  
{
	TankAimingComponent = AimingComponent;
	MyBarrel = TankBarrel;  

	if (TankAimingComponent == nullptr || MyBarrel==nullptr) //Pointer Protection Log only.
	{
		UE_LOG(LogTemp, Warning, TEXT("NULLPTR on ATank::SetAimComponent()"));
	}
}

void ATank::Fire()
{
	//Check if ready to fire, by seeing how many seconds have passed since the last shot. This is better than setting the value to 0 manually.
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastShotTime) > ReloadTimeInSeconds;

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
			LastShotTime = GetWorld()->GetTimeSeconds();
		}
	}
}


