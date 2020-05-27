workspace "BucketSortMPI"
    configurations { "Debug", "Release" }
    architecture "x64"
    platforms { "Win64" }

    CPPDIALECT = "C++17"

    TARGET_DIR = "%{wks.location}/../bin/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"
    OUTPUT_DIR = "%{wks.location}/../bin/obj/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"

    filter "action:vs*"
        buildoptions {"/Zc:__cplusplus"}

    filter "system:windows"
        systemversion "latest"

    project "BucketSortMPI"
        language "C++"
        cppdialect (CPPDIALECT)
        targetdir (TARGET_DIR)
        objdir (OUTPUT_DIR .. "/%{prj.name}")

        files { "**.hpp", "**.cpp" }

        filter "configurations:Debug"
            kind "ConsoleApp"
            defines { "DEBUG" }
            symbols "On"
            runtime "Debug"

        filter "configurations:Release or Dist"
            kind "WindowedApp"
            defines { "NDEBUG", "RELEASE"}
            optimize "On"
            runtime "Release"
