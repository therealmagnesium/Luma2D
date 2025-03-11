workspace("Luma2D")
architecture("x64")

configurations({
    "Debug",
    "Release",
    "Dist",
})

include("vendor/imgui")
include("Luma2D")
include("LumaEditor")
