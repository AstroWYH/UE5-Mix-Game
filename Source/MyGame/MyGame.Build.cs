// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyGame : ModuleRules
{
	public MyGame(ReadOnlyTargetRules Target) : base(Target)
	{
        OptimizeCode = CodeOptimization.Never;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Slate", "SlateCore" });

        PublicIncludePaths.AddRange(new string[]
        {
            "MyGame",
            "MyGame/Character",
            "MyGame/DataTable",
            "MyGame/Subsystem",
        });
    }
}
