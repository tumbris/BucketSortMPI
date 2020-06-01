workspace "BucketSortOMP"
    configurations { "Debug", "Release" }
    architecture "x64"
    platforms { "Win64" }

    CPPDIALECT = "C++17"

    TARGET_DIR = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"
    OUTPUT_DIR = "%{wks.location}/bin/obj/%{cfg.buildcfg}-%{cfg.platform}-%{cfg.architecture}"


    filter "action:vs*"
        buildoptions 
        {
            "/Zc:__cplusplus",
        }

    filter "system:windows"
        systemversion "latest"

    project "BucketSortOpenMP"
        kind "ConsoleApp"
        language "C++"
        cppdialect (CPPDIALECT)
        targetdir (TARGET_DIR)
        objdir (OUTPUT_DIR .. "/%{prj.name}")

        files { "%{prj.location}/**.hpp", "%{prj.location}/**.cpp" }

        filter "action:vs*"
            buildoptions 
            {
                "/openmp"
            }

        includedirs {"%{prj.location}"}

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            runtime "Debug"

        filter "configurations:Release"
            defines { "NDEBUG", "RELEASE"}
            optimize "On"
            runtime "Release"
