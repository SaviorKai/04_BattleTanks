// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ABattleTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
};

/// ORDER OF RUNTIME
/* Notes:
// - Looks like bp_GameMode Construction script doesn't run? 
// - Seems like BLUEPRINT Construction script is skipped for the AI Units already placed in the level?

*** 1. Class Constructors ***
	[SAVIORKAI C++] : ATank Constructor
	[SAVIORKAI C++] : UTankTurret Construction
	[SAVIORKAI C++] : UTankMovementComponent Construction
	[SAVIORKAI C++] : UTankTrack Construction
	[SAVIORKAI C++] : UTankAimingComponent Construction
	[SAVIORKAI C++] : UTankTrack Construction
	[SAVIORKAI C++] : UTankBarrel Construction

	[bp_PlayerController_C_0] [SAVIORKAI] : bp_PlayerController, Construction Script
	[SAVIORKAI C++] : ATank Constructor
	[SAVIORKAI C++] : UTankTurret Construction
	[SAVIORKAI C++] : UTankBarrel Construction
	[SAVIORKAI C++] : UTankTrack Construction
	[SAVIORKAI C++] : UTankTrack Construction
	[SAVIORKAI C++] : UTankMovementComponent Construction
	[SAVIORKAI C++] : UTankAimingComponent Construction

*** 2. BP Class Constructors ***
	[bp_Tank_C_0] [SAVIORKAI] : bp_Tank, Construction Script

*** 3. Game Mode BP Begin Play ***
	[bp_Game_Mode_C_0] [SAVIORKAI] :bp_Game_Mode, BeginPlayEvent

*** 4. Units Already in Level ***
	[SAVIORKAI C++] : ATankAIController BeginPlay
	[SAVIORKAI C++] : UTankAimingComponent BeginPlay()
	[bp_Tank_2] [SAVIORKAI] : bp_Tank, BeginPlayEvent (Inisialise Functions)
	[SAVIORKAI C++] : ATank BeginPlay

*** 5. Level Blueprint (After Unites spawned into level)
	[lvl_Main_C_14] [SAVIORKAI] : lvl_Main BP, BeginPlayEvent

*** 6. PlayerController + Units (Construction happened earlier in step 1 & 2)
	[bp_PlayerController_C_0] [SAVIORKAI] : bp_PlayerController, BeginPlayEvents
	[SAVIORKAI C++] : UTankAimingComponent BeginPlay()
	[bp_Tank_C_0] [SAVIORKAI] : bp_Tank, BeginPlayEvent (Inisialise Functions)
	[SAVIORKAI C++] : ATank BeginPlay

*/
