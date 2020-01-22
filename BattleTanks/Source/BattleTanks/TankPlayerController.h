// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

///Must Be the last Include
#include "TankPlayerController.generated.h"

//Forward Declaration
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;				/// Called when the game starts or when spwned (Ivan added)
	virtual void Tick(float DeltaTime) override;	/// Called every tick/step of the game (Ivan added)

	UFUNCTION(BlueprintPure, Category = "Score")
	float GetMyScore();

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingComponent); //IVAN NOTE: We don't need to DEFINE this function, since we are using 'BlueprintImplementableEvent'

private:
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationX = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationY = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const; //Out Param Method, true if hit something
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const; //Out Param Method
	bool GetLookVectorHitLocation(FVector CamLookDirection, FVector& HitLocationPoint) const;
	
	/// This Function is called by the engine AIController class, when it posseses a pawn. We intercept it. 
	virtual void SetPawn(APawn* InPawn) override;

	//[DMCD Step 4] Declare Delegate Listener (method to execute when delegate is called)
	UFUNCTION()
		void OnPossesedTankDeath();

	float MyPlayerScore = 0.0f;
	
};
