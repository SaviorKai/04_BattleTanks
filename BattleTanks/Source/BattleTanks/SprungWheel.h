// Copyright Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"


class UPhysicsConstraintComponent;


UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	/// Components
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* RootMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WheelConstraintMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		UPhysicsConstraintComponent* PhysicsConstraint = nullptr;


};
