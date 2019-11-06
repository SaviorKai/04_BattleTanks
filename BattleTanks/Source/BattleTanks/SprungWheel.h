// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"


class UPhysicsConstraintComponent;
class USphereComponent;

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
	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SpringPhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxlePhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")					// Reminder that Blueprint Read only won't work in Private. 
		USphereComponent* WheelMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* AxleMesh = nullptr;						// We are using USphereComponenthere, as they can be invisible if we want (no mesh)





};
