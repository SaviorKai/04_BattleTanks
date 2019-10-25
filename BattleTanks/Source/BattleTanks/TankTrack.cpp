// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
//#include "Components/SceneComponent.h"


UTankTrack::UTankTrack() /// [REMOVE]
{
	UE_LOG(LogTemp, Warning, TEXT("[SAVIORKAI C++] : UTankTrack Construction"));
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
