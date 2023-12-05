-- premake5.lua
include "preprocess.lua"

workspace "Engine"
    configurations {"Debug", "Release"}
    platforms {"Win64", "Linux"}

project "Engine"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"
    objdir ("obj/%{cfg.platform}/%{cfg.buildcfg}")
    toolset "clang"

    includedirs {"headers"}
    files {"src/**.cpp"}

    filter "configurations:Debug"
    
    defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"