// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NekoSplash : ModuleRules
{
	public NekoSplash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"DeveloperSettings",
				"UnrealEd",
				
				// Forced to add to dependency because want to use GetWindowsSplashFilename() directly
				"SharedSettingsWidgets",
				"AudioSettingsEditor",
				"EditorStyle",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
