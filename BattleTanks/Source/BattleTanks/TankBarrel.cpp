// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "TankBarrel.h"

void UTankBarrel::Elevate(float ElevatePosition)
{
	//move the barrel the right amount this frame
	//given a max elevation speed, and frame time (delta seconds)
	
	//Calculate the speed it moves per frame
	ElevatePosition = FMath::Clamp<float>(ElevatePosition, -1, 1);
	auto ElevationChangeSpeed = (ElevatePosition * MaxDegreesPerSecond) * GetWorld()->GetDeltaSeconds();
	
	//Calculate the new rotation value it needs to be this frame, relative to its current rotation.
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChangeSpeed;
	auto ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);

	//Update the rotation of the component with the new calculated values. 
	SetRelativeRotation((FRotator(ClampedNewElevation, 0, 0)));



	


	
}
