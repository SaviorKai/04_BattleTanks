// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Components/SceneComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	///1. Register the OnHit() Event delegate:
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Calculate the Slipping Speed
	auto SlippingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	
	// Calculate the Correction Acceleration required
	auto CorrectionAcceleration = -SlippingSpeed / DeltaTime * GetRightVector(); // Negative of Slipping speed, since we want to go the opposite direction / Deltatime * GetRightVector(), thus scaling the vector of get right by the number of -Slippingspeed/deltatime.

	// Calculate and apply sideways velocity.
	auto TankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = ((TankRootMesh->GetMass() * CorrectionAcceleration)/2); //We devide by two here, since we have two tracks. 
	TankRootMesh->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ONHIT Cpp Working"));
}

void UTankTrack::SetThrottle(float Amount)
{
	auto MyName = GetName();
	auto ForceApplied = GetForwardVector() * Amount * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto MyTankRoot = GetOwner()->GetRootComponent(); //This is a good way to get the root component.
	auto TankRootConverted = Cast<UPrimitiveComponent>(MyTankRoot); // Cast down to a child class of USceneComponent, to make it a UPrimitiveComponent.
	
	TankRootConverted->AddForceAtLocation(ForceApplied, ForceLocation);
	// TODO: Set max track speed to a CLAMP to ensure that DOUBLE controlls, can't double the speed. Do this by creating a MySpeedVar, and have this function alter it instead.
}
