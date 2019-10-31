// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Components/SceneComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	///1. Register the OnHit() Event delegate:
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//When Tank is touching the ground, only then apply Driving Force and Sideways Friction this tick:
	DriveTrack();
	ApplySidewaysForce();
	//Once Forces are applied, reset the Throttle to 0, to ensure it doesn't always stay at 1.
	Throttle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the Slipping Speed
	auto SlippingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Calculate the Correction Acceleration required
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippingSpeed / DeltaTime * GetRightVector(); // Negative of Slipping speed, since we want to go the opposite direction / Deltatime * GetRightVector(), thus scaling the vector of get right by the number of -Slippingspeed/deltatime.

																				 // Calculate and apply sideways velocity.
	auto TankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = ((TankRootMesh->GetMass() * CorrectionAcceleration) / 2); //We devide by two here, since we have two tracks. 
	TankRootMesh->AddForce(CorrectionForce);
}



void UTankTrack::SetThrottle(float Amount)
{
	//Clamp Throttle (Throttle is set as a var in the header, so that we can get it's current value.
	Throttle = FMath::Clamp<float>(Throttle + Amount, -1,1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto MyTankRoot = GetOwner()->GetRootComponent(); //This is a good way to get the root component.
	auto TankRootConverted = Cast<UPrimitiveComponent>(MyTankRoot); // Cast down to a child class of USceneComponent, to make it a UPrimitiveComponent.

	TankRootConverted->AddForceAtLocation(ForceApplied, ForceLocation);
	//TODO: Rethink turning throttles. It interfere's with the forward motion, which means they work against one another.
}
