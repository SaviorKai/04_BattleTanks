// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//Forward Declarations
class UTankProjectileMovementComponent;

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
};
