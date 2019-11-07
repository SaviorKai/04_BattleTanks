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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/// Components
	void SetupConstraint();

	float CurrentDrivingForce = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SpringPhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxlePhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")							// Reminder that Blueprint Read only won't work in Private. 
		USphereComponent* WheelMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* AxleMesh = nullptr;									// We are using USphereComponenthere, as they can be invisible if we want (no mesh)

	//* 2. Create the Delegate Function in our class, and ensure the signature is the same as the OnHitComponent, since it will pass the same arugements.      
	//* Remember: we removed the first few items from the Signature (FComponentHitSignature, UPrimitiveComponent, OnComponentHit,), and the additional ',' commas inbetween. 
	UFUNCTION() //THIS MUST ALWAYS BE A UFUNCTION if you want to register OnHit. This does not need to be defined.																								
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);   //TODO Document this better.



};
