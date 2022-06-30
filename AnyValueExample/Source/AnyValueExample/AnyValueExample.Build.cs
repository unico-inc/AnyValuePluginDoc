// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnyValueExample : ModuleRules
{
	public AnyValueExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"AnyValue",		// Add dependent modules
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
