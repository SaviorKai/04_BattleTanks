// All rights reserved © 2019 Ivan Carl Engelbrecht

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTanksTarget : TargetRules
{
	public BattleTanksTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "BattleTanks" } );
	}
}
