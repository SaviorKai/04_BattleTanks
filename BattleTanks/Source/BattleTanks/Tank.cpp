// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h" //Supporting the Forward Declaration

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

void ATank::SetBarrelReference(UTankBarrel* TankBarrel)
{
	TankAimingComponent->SetBarrelReferenceAimComponent(TankBarrel);
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

