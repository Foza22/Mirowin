// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mirowin : ModuleRules
{
	public Mirowin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"HeadMountedDisplay",
				"GameplayTasks",
				"NavigationSystem"
			});

		PublicIncludePaths.AddRange(new string[]
		{
			"Mirowin/Public/Character",
			"Mirowin/Public/UI",
			"Mirowin/Public/Interactions",
			"Mirowin/Public/Components",
			"Mirowin/Public/Weapon",
			"Mirowin/Public/AI",
			"Mirowin/Public/AI/Tasks",
		});
	}
}