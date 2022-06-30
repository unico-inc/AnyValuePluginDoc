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
			"AnyValue",		// 依存モジュールを追加.
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
