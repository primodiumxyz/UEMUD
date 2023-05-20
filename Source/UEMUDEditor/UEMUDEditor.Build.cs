using UnrealBuildTool;

public class UEMUDEditor : ModuleRules
{
	public UEMUDEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "UEMUD","HTTP",
				"Json",
				"JsonUtilities"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"UEMUD",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"ContextFramework", "TurboLinkGrpc",  "StructUtils","DeveloperSettings", "web3Unreal","HTTP",
				"Json",
				"JsonUtilities"
			}
		);
	}
}