local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Test")
kind("SharedLib")
language("C++")
cppdialect("C++17")
systemversion("latest")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/Test/Test.h",
    "source/Test/Test.cpp",
})

includedirs({
    "../Luma2D/source",
})

libdirs({})

links({
    "raylib",
})

postbuildcommands({
    --"cp -r assets/ %{cfg.buildtarget.directory}",
    --"cp -r scenes/ %{cfg.buildtarget.directory}",
    --"cp ../imgui.ini %{cfg.buildtarget.directory}",
})

filter("system:linux")
links({})
defines({
    "PLATFORM_LINUX",
})

filter("system:windows")
links({})
defines({
    "PLATFORM_WINDOWS",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")

project("LumaEditor")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")
systemversion("latest")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/*.h",
    "source/*.cpp",
})

includedirs({
    "../Luma2D/source",
})

libdirs({})

links({
    "Luma2D",
})

postbuildcommands({
    --"cp -r assets/ %{cfg.buildtarget.directory}",
    --"cp -r scenes/ %{cfg.buildtarget.directory}",
    --"cp ../imgui.ini %{cfg.buildtarget.directory}",
})

filter("system:linux")
links({})
defines({
    "PLATFORM_LINUX",
})

filter("system:windows")
links({})
defines({
    "PLATFORM_WINDOWS",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")
