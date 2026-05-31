// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ashfall : ModuleRules
{
	public Ashfall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Ashfall",
			"Ashfall/Variant_Platforming",
			"Ashfall/Variant_Platforming/Animation",
			"Ashfall/Variant_Combat",
			"Ashfall/Variant_Combat/AI",
			"Ashfall/Variant_Combat/Animation",
			"Ashfall/Variant_Combat/Gameplay",
			"Ashfall/Variant_Combat/Interfaces",
			"Ashfall/Variant_Combat/UI",
			"Ashfall/Variant_SideScrolling",
			"Ashfall/Variant_SideScrolling/AI",
			"Ashfall/Variant_SideScrolling/Gameplay",
			"Ashfall/Variant_SideScrolling/Interfaces",
			"Ashfall/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
