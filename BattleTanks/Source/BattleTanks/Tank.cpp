// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankTrack.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;    /// IVAN NOTE: We set this to false to improve performance! We don't need tick here.

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Set the starting Health (This needs to be set here, since the health might be set in the Blueprint). 
	MyHealth = StartingHealth;
}

/// Called by the Engine when Actor Damage is dealt.
float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 ClampedDamage = FMath::Clamp<int32>(DamageAmount, 0, MyHealth);
	MyHealth -= ClampedDamage;

	if (MyHealth <= 0)
	{
		///[DMCD Step 3] Broadcast
		OnDeath.Broadcast();
	}
	

	return ClampedDamage;
}


float ATank::GetHealthPercent()
{
	return (float)MyHealth / (float)StartingHealth;			///NOTE: Remember that these values are not floats, they are ints. Thus, we cast them to (float) to ensure we get a float return. 
}
