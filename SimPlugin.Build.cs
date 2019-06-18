/*
 * Build script for SimPlugin
 *
 * Copyright (C) 2018 Simon D. Levy
 *
 * MIT License
 */


using UnrealBuildTool;
using System;
using System.IO;

public class SimPlugin : ModuleRules
{
    public SimPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
                { "Core", "CoreUObject", "Engine", "InputCore", "MulticopterSim" });

        string home = Environment.GetEnvironmentVariable("userprofile");

        PrivateIncludePaths.Add(home + "\\Documents\\Arduino\\libraries\\Hackflight\\src");

        string python = home + "\\AppData\\Local\\Programs\\Python\\Python36";

        PrivateIncludePaths.Add(python + "\\include");

        PublicLibraryPaths.Add(python + "\\libs");
    }
}
