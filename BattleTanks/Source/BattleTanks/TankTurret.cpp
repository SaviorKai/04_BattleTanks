// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RotationPosition)
{
	//Normalize the value of the position to be used accurately with speed
	RotationPosition = FMath::Clamp<float>(RotationPosition, -1, 1);
	
	//Calculate the final rotation amount per frame
	auto RotationChangeSpeed = (RotationPosition * MaxRotationPerSecond) * GetWorld()->GetDeltaSeconds();
	auto FinalRotation = RelativeRotation.Yaw + RotationChangeSpeed;
		
	//Rotate the turret
	SetRelativeRotation(FRotator(0, FinalRotation, 0));
	
}