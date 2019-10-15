// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
//#include "Engine.h"

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
}

void UTankAimingComponent::TurnAndAimAt(FVector TargetLocation, float LaunchSpeed)
{
	///DEBUG LOGS
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s. Barrel Posision is: %s"), *GetOwner()->GetName(), *TargetLocation.ToString(), *MyTankBarrel->GetComponentLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("LaunchSpeed is %f"), LaunchSpeed);
}

void UTankAimingComponent::SetBarrelReferenceAimComponent(UStaticMeshComponent* TankBarrel)
{
	//Set the Private Member Var from input.
	MyTankBarrel = TankBarrel;
}

