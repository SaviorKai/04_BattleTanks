// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
//#include "Components/SceneComponent.h"


UTankTrack::UTankTrack() /// Ivan added. Constructor.
{
	//UE_LOG(LogTemp, Warning, TEXT("Tracks reporting for duty!"));
}

void UTankTrack::SetThrottle(float Amount)
{
	auto MyName = GetName();
	

	//TODO: Clamp Throttle value to 1 and 0 to avoid player overdrive.

	auto ForceApplied = GetForwardVector() * Amount * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto MyTankRoot = GetOwner()->GetRootComponent(); //This is a good way to get the root component.
	auto TankRootConverted = Cast<UPrimitiveComponent>(MyTankRoot); // Cast down to a child class of USceneComponent, to make it a UPrimitiveComponent.
	
	TankRootConverted->AddForceAtLocation(ForceApplied, ForceLocation);
}
