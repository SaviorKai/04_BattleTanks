// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move the barrel the right amount this frame
	//given a max elevation speed, and frame time (delta seconds)
	
	//Calculate the speed it moves per frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChangeSpeed = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	//Calculate the new rotation value it needs to be this frame, relative to its current rotation.
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChangeSpeed;
	auto ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);

	//Update the rotation of the component with the new calculated values. 
	SetRelativeRotation((FRotator(ClampedNewElevation, 0, 0)));



	


	
}
