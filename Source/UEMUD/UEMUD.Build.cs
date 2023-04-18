using UnrealBuildTool;

public class UEMUD : ModuleRules
{
    public UEMUD(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "ContextFramework", "TurboLinkGrpc", "web3Unreal","HTTP",
                "Json",
                "JsonUtilities"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
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