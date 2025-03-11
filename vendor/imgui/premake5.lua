project("imgui")
kind("StaticLib")
language("C++")
cppdialect("C++17")

targetdir("bin")
objdir("build")
pic("on")

files({
    "include/*.h",
    "source/*.cpp",
})

includedirs({
    "include",
})

libdirs({})

links({})

filter("system:Unix")
system("linux")
systemversion("latest")
defines({
    "PLATFORM_LINUX",
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
