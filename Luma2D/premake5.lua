local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Luma2D")
kind("SharedLib")
language("C++")
cppdialect("C++17")
systemversion("latest")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
	"source/Core/**.h",
	"source/Core/**.cpp",
})

includedirs({
	"source",
	"../LumaEditor/source/Test",
})

libdirs({})

links({
	"raylib",
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

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
