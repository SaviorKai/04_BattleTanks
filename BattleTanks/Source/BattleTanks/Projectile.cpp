// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankProjectileMovementComponent.h"


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

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	///1. Register the OnHit() Event delegate:
	ProjMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);     ///NOTE: This wasn't added on the core class, since this isn't a component class. BUT the static mesh we add, is.
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
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
}

