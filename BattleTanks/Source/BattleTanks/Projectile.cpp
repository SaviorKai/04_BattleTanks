// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"		//Forward Declaration Include
#include "Components/StaticMeshComponent.h"			//Forward Declaration Include
#include "TankProjectileMovementComponent.h"		//Forward Declaration Include
#include "PhysicsEngine/RadialForceComponent.h"		//Forward Declaration Include
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/AudioComponent.h"



#define OUT

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/// Add the projectile mesh component
	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(ProjMesh);							//We set the Root component here, to ensure it doesn't accidentally make something else the root.
	ProjMesh->SetNotifyRigidBodyCollision(true);		//This always turns on "Simulation Generates Hit Events" checkbox as default.  //TODO: do this for all your classes to avoid manual setup when created as new.
	ProjMesh->SetVisibility(false);						//Turned this off by default, since we won't have a mesh. We'll be using particle smoke.
	//ProjMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Units/Projectiles/mesh_Projectile.mesh_Projectile")));  //Code to apply a mesh to this object.

	/// Add the Projectile particle system
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));					// IVAN NOTE: If we don't assign them to a var and make it a UPROPERTY(VisibleAnywhere), we can't see the details in the editor.
	LaunchBlast->AttachTo(RootComponent);																	//Attaches this to the root component.

	/// Add the ImpactBlast
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);		//ALTERNATIVE way to Attach this to a component.
	ImpactBlast->bAutoActivate = false;																		//Ensures this doesn't activate at the start.


	/// Add the projectile movement component
	ProjMoveComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("TankProjectileMovement"));
	ProjMoveComponent->bAutoActivate = false;

	/// Create the explosion radial force
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Radial Force"));
	ExplosionForce->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	///1. Register the OnHit() Event delegate:
	ProjMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);     ///NOTE: This wasn't added on the core class, since this isn't a component class. BUT the static mesh we add, is.


	//Play SpawnSound
	if (Sound_Spawn)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound_Spawn, GetActorLocation());
	}
	//Attach Traveling Sound
	if (Sound_ProjectileTraveling)
	{
		MyTravelingSound = UGameplayStatics::SpawnSoundAttached(Sound_ProjectileTraveling, ProjMesh, NAME_None);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjMoveComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjMoveComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/// Particle Systems
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

	///Play ImpactSound
	if (Sound_Impact)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound_Impact, GetActorLocation());
	}
	///StopSoundTraveling
	if (MyTravelingSound)
	{
		MyTravelingSound->Stop();
	}
	
	/// Explosion Radial Force for Physics.
	ExplosionForce->FireImpulse(); 

	///Destroy the Mesh and set new root
	SetRootComponent(ImpactBlast);
	ProjMesh->DestroyComponent();

	//Damage Enemy Tank					
	UGameplayStatics::ApplyRadialDamage(	//IVAN NOTE: This calls the AActor::TakeDamage method. We intercept this method in the Tank.cpp.
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,				// For consistency, and so that we can change both vars together.
		UDamageType::StaticClass(),
		TArray<AActor*>()					// Damage all Actors (who this should affect).
	);

	///Get timer to destroy this Actor
	FTimerHandle Timer01;
	GetWorld()->GetTimerManager().SetTimer(
		OUT Timer01,						// OUT parameter, we need it.
		this,								
		&AProjectile::OnTimer01Expire,		//The method we call when this expires ///TODO: 1. Why do we use the reference '&' on &AProjectile::OnTimerExpire?    2. Why don't we use () at the end of the 'OnTimerExpire' method name? ANSWER: This is because 1. Thats an Address "&of"  and 2. We're passing the address of the function (we don't want to execute it right now, we want to execute it when the timer expires). See more here: https://godbolt.org/z/h2QPhc
		DestroyDelay,						//The time for the timer (in float. default = 5);
		false								//Let the timer loop (true), or run only once(false).
	);
}

void AProjectile::OnTimer01Expire()
{
	Destroy();
}

