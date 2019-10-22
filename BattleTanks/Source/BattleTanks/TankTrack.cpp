// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


UTankTrack::UTankTrack() /// Ivan added. Constructor.
{
	//UE_LOG(LogTemp, Warning, TEXT("Tracks reporting for duty!"));
}

void UTankTrack::SetThrottle(float Amount)
{
	auto MyName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s, Throttle amount: %f"), *MyName, Amount);

	//TODO: Clamp Throttle value to 1 and 0 to avoid player overdrive.
}
