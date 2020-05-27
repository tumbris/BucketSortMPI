workspace "BucketSortMPI"
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
            "/openmp"
        }

    filter "system:windows"
        systemversion "latest"

    project "BucketSortMPI"
        kind "ConsoleApp"
        language "C++"
        cppdialect (CPPDIALECT)
        targetdir (TARGET_DIR)
        objdir (OUTPUT_DIR .. "/%{prj.name}")

        files { "**.hpp", "**.cpp" }

        links { "msmpi" }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            runtime "Debug"

        filter "configurations:Release"
            defines { "NDEBUG", "RELEASE"}
            optimize "On"
            runtime "Release"

            
        filter "system:windows"
            includedirs
            {
                "\"" .. os.getenv("MSMPI_INC") .. "\""
            }
            
            libdirs
            {
                "\"" .. os.getenv("MSMPI_LIB64") .. "\""
            }

