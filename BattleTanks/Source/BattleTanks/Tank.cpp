// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Engine/World.h"

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
	
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //TODO: What was this used for? 

}



