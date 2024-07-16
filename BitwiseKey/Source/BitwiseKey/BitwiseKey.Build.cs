// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BitwiseKey : ModuleRules
{
	public BitwiseKey(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "CommonInput" });
	}
}
