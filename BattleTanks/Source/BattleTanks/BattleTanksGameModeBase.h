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
// - Units within a level(AI), will not run their Construction script if you don't load another level before it (like a main menu).

========== Menu Level ==========
*** 0. Pre-Constructors (C++ > BP)
	[bp_PlayerController_C_0] [SAVIORKAI] : bp_PlayerController, Construction Script
		[SAVIORKAI C++] : ATank Constructor
		[bp_Tank_C_0] [SAVIORKAI] : bp_Tank, Construction Script

****1. Begin Play (C++ > BP)
	[bp_Game_Mode_C_0] [SAVIORKAI] :bp_Game_Mode, BeginPlayEvent
	[bp_PlayerController_C_0] [SAVIORKAI] : bp_PlayerController, BeginPlayEvents
		[SAVIORKAI C++] : ATank BeginPlay
		[SAVIORKAI C++] : UTankAimingComponent BeginPlay()
		[bp_Tank_C_0] [SAVIORKAI] : bp_Tank, BeginPlayEvent (Inisialise Functions)


========== Main Tank Level + Pre-Constructors ================
*** 0. Pre-Constructors (C++ > BP)         //NOTE: This is skipped another level isn't loaded before Main Tank Level)
	[SAVIORKAI C++] : ATank Constructor
	[bp_Tank_2] [SAVIORKAI] : bp_Tank, Construction Script

*** 0. Constructors (C++ > BP)
	[bp_PlayerController_C_0] [SAVIORKAI] : bp_PlayerController, Construction Script
		[SAVIORKAI C++] : ATank Constructor
		[bp_Tank_C_0] [SAVIORKAI] : bp_Tank, Construction Script

****1. Begin Play (C++ > BP)
	[bp_Game_Mode_C_0] [SAVIORKAI] :bp_Game_Mode, BeginPlayEvent
	[SAVIORKAI C++] : ATankAIController BeginPlay
		[SAVIORKAI C++] : ATank BeginPlay
		[SAVIORKAI C++] : UTankAimingComponent BeginPlay()
		[bp_Tank_2] [SAVIORKAI] : bp_Tank, BeginPlayEvent (Inisialise Functions)
	[lvl_Main_C_16] [SAVIORKAI] : lvl_Main BP, BeginPlayEvent
	[bp_PlayerController_C_0] [SAVIORKAI] : bp_PlayerController, BeginPlayEvents
		[SAVIORKAI C++] : ATank BeginPlay
		[SAVIORKAI C++] : UTankAimingComponent BeginPlay()
		[bp_Tank_C_0] [SAVIORKAI] : bp_Tank, BeginPlayEvent (Inisialise Functions)

*/
