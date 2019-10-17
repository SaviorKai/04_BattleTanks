// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#define OUT

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
	if (MyTankBarrel == nullptr) { return; } //Pointer Protection

	
	FVector TossVelocity(0);

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,			// World context object. Grabs the class we're currently in. In this case, TankAimingComponent.cpp.
		OUT TossVelocity,
		MyTankBarrel->GetSocketLocation(FName("ProjectileSpawn")),
		TargetLocation,
		LaunchSpeed,
		false,      //IVAN NOTE: You don't need these paramaters, since they are default. You can delete them and it would still work.
		0,			//IVAN NOTE: You don't need these paramaters, since they are default. You can delete them and it would still work.
		0,			//IVAN NOTE: You don't need these paramaters, since they are default. You can delete them and it would still work.
		ESuggestProjVelocityTraceOption::DoNotTrace //NOTE! This argument is required for this function to work!
	);

	if (bHaveAimSolution)
	{
		//Normalize the value of TossVelocity to a combined directional value of 1 with GetSafeNormal().
		FVector AimDirection = TossVelocity.GetSafeNormal();

		///Move the barrel to aim at the solution location. 
		MoveBarrel(AimDirection);


		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IMPOSSIBLE TossVelocity!!"));
	}
	



	///DEBUG LOGS
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s. Barrel Posision is: %s"), *GetOwner()->GetName(), *TargetLocation.ToString(), *MyTankBarrel->GetComponentLocation().ToString());
}

void UTankAimingComponent::SetBarrelReferenceAimComponent(UStaticMeshComponent* TankBarrel)
{
	//Set the Private Member Var from input.
	MyTankBarrel = TankBarrel;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//Work out the difference between the two points
	FRotator BarrelRotation = MyTankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;

	UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation: %s , AimAsRotator is %s"), *BarrelRotation.ToString(), *AimAsRotator.ToString());
	//move the barrel the right amount this frame
	//given a max elevation speed, and frame time (delta seconds)
	
}

