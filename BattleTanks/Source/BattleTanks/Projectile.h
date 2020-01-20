// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//Forward Declarations
class UTankProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class URadialForceComponent;

//Must be last include
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Public Methods
	void LaunchProjectile(float Speed);

private:
	//Private Vars
	UTankProjectileMovementComponent* ProjMoveComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ProjMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
		USoundBase* Sound_Spawn = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		USoundBase* Sound_Impact = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		USoundBase* Sound_ProjectileTraveling = nullptr;

	UAudioComponent* MyTravelingSound = nullptr;

	
	
	UPROPERTY(VisibleAnywhere)
		URadialForceComponent* ExplosionForce = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
		float DestroyDelay = 5.0f;
	
	UPROPERTY(EditDefaultsOnly)
		float ProjectileDamage = 50.0f;
	

	//Private Methods
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);  //2. Use this signature for the delegate (OnHit()) NOTE: UFUNCTION() is required! 

	void OnTimer01Expire();
};
