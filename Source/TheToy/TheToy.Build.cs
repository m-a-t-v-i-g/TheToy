// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheToy : ModuleRules
{
	public TheToy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Slate", "SlateCore", "UMG"
		});
		
		PublicIncludePaths.AddRange(new[]
		{
			"TheToy",
			"TheToy/Characters",
			"TheToy/Components",
			"TheToy/Input",
			"TheToy/Player"
		});
	}
}
