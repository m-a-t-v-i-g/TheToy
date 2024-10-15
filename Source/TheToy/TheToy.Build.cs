// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheToy : ModuleRules
{
	public TheToy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule"
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Slate", "SlateCore", "UMG"
		});
		
		PublicIncludePaths.AddRange(new[]
		{
			"TheToy",
			"TheToy/AI",
			"TheToy/Characters",
			"TheToy/Components",
			"TheToy/Game",
			"TheToy/Input",
			"TheToy/Player"
		});
	}
}
