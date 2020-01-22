// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "Tank.h"
#include "TankTrack.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


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

	//Attach Engine Idle Sound
	if (Sound_EngineIdle)
	{
		MyEngine_IdleSound = UGameplayStatics::SpawnSoundAttached(Sound_EngineIdle, GetRootComponent(), NAME_None);
	}
}

void ATank::AddScore(int32 Amount)
{
	MyScore += Amount;
}



/// Called by the Engine when Actor Damage is dealt.
float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 ClampedDamage = FMath::Clamp<int32>(DamageAmount, 0, MyHealth);
	MyHealth -= ClampedDamage;

	if (MyHealth <= 0 && bHasDied == false)
	{
		bHasDied = true;

		///[DMCD Step 3] Broadcast
		OnDeath.Broadcast();
		
		//Death Effects
		PlayDeathFx();

		//Stop Engine Idle Sounds
		if (MyEngine_IdleSound)
		{
			MyEngine_IdleSound->FadeOut(3.0f,0.0f);
			
		}
		if (MyEngine_MovingSound)
		{
			MyEngine_MovingSound->FadeOut(2.0f, 0.0f);
		}

		//PlayTankFlame Sounds
		if (Sound_TankDeathFlames)
		{
			UGameplayStatics::SpawnSoundAttached(Sound_TankDeathFlames, GetRootComponent(), NAME_None);
		}

		//Add Score if Killer is Player
		auto MyTempPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
		Cast<ATank>(MyTempPawn)->AddScore(10);

	}
	

	return ClampedDamage;
}


float ATank::GetHealthPercent()
{
	return (float)MyHealth / (float)StartingHealth;			///NOTE: Remember that these values are not floats, they are ints. Thus, we cast them to (float) to ensure we get a float return. 
}


float ATank::GetScore()
{
	return MyScore;
}

void ATank::CounterSliding()
{
	auto MyMeshComp = Cast<UStaticMeshComponent>(GetRootComponent());
	if (!MyMeshComp) { return; }
	
	auto TankRightVector = MyMeshComp->GetRightVector().GetSafeNormal();
	auto MyVelocity = GetVelocity().GetSafeNormal();

	auto DotProductResult = FVector::DotProduct(TankRightVector, MyVelocity);

	float CounterForce = -DotProductResult * (MyMeshComp->GetMass() *2000);
	
	auto CounterForceApplied = MyMeshComp->GetRightVector() * CounterForce;

	MyMeshComp->AddForce(CounterForceApplied, NAME_None, false);
	
}

void ATank::PlayEngineMoveSound()
{
	//Attach Engine Idle Sound
	if (Sound_EngineMovement)
	{
		if (!MyEngine_MovingSound)
			{
				MyEngine_MovingSound = UGameplayStatics::SpawnSoundAttached(Sound_EngineMovement, GetRootComponent(), NAME_None);
				MyEngine_MovingSound->FadeIn(0.1f, 1.0f);
			}
	}
}

void ATank::StopEngineMoveSound()
{
	//Attach Engine Idle Sound
	if (Sound_EngineMovement)
	{
		if (MyEngine_MovingSound)
		{
			MyEngine_MovingSound->FadeOut(0.25f,0.0f);
			MyEngine_MovingSound = nullptr;
		}
	}
}
