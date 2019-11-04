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
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 ClampedDamage = FMath::Clamp<int32>(DamageAmount, 0, MyHealth);
	MyHealth -= ClampedDamage;

	if (MyHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK DIED."), DamagePoints, ClampedDamage, MyHealth);
	}
	

	return ClampedDamage;
}



