workspace "InvadersVS"
	architecture "x86_64"
	
	-- Build Configurations...
    configurations { 
		"Debug",
		"Release" 
		}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["SFML"] = "InvadersVS/vendor/SFML/include"

project "InvadersVS"
	location "InvadersVS"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp" 
	}

	includedirs {
		"../%{prj.name}/src/",
		"%{IncludeDir.SFML}"
	}

	libdirs {
		"InvadersVS/vendor/SFML/lib"
		}

	links {		

	}

	filter "system:windows"
	cppdialect "C++17"
    systemversion "latest"

	defines { 
		"GAME_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "GAME_DEBUG"
		runtime "Debug"
		symbols "On"

    links { 
		"sfml-audio-d.lib", 
		"sfml-graphics-d.lib", 
		"sfml-network-d.lib", 
		"sfml-system-d.lib", 
		"sfml-window-d.lib",

		"kernel32.lib", 
		"user32.lib", 
		"gdi32.lib", 
		"winspool.lib", 
		"comdlg32.lib", 
		"advapi32.lib", 
		"shell32.lib", 
		"ole32.lib", 
		"oleaut32.lib", 
		"uuid.lib", 
		"odbc32.lib", 
		"odbccp32.lib"
		}

	filter "configurations:Release"
		defines "GAME_PUBLIC"
		runtime "Release"
		optimize "On"

    links { 
		"sfml-audio.lib", 
		"sfml-graphics.lib", 
		"sfml-network.lib", 
		"sfml-system.lib", 
		"sfml-window.lib",

		"kernel32.lib", 
		"user32.lib", 
		"gdi32.lib", 
		"winspool.lib", 
		"comdlg32.lib", 
		"advapi32.lib", 
		"shell32.lib", 
		"ole32.lib", 
		"oleaut32.lib", 
		"uuid.lib", 
		"odbc32.lib", 
		"odbccp32.lib"
		}