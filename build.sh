#!/bin/bash

config="$1"
appName="LumaEditor"

if [[ $config = "run" ]]; then
    mode="$2"
    system="$3"

    if [[ $mode = "debug" ]]; then
        cd "bin/Debug-$system/$appName"
        ./$appName
    elif [[ $mode = "release" ]]; then
        cd "bin/Release-$system/$appName"
        ./$appName
    elif [[ $mode = "dist" ]]; then
        cd "bin/Dist-$system/$appName"
        ./$appName
    fi
elif [[ $config = "assets" ]]; then
    mode="$2"
    system="$3"
    if [[ $mode = "debug" ]]; then
        cp -r "App/assets/" "bin/Debug-$system/LumaEditor/"
    elif [[ $mode = "release" ]]; then
        cp -r "App/assets/" "bin/Release-$system/LumaEditor/"
    elif [[ $mode = "dist" ]]; then
        cp -r "App/assets/" "bin/Dist-$system/LumaEditor/"
    fi
elif [[ $config = "ecc" ]]; then
    system="$2"
    premake5 export-compile-commands
    cp "compile_commands/debug.json" "compile_commands.json"
elif [[ $config = "clean" ]]; then
    rm -rf bin build
    rm -rf vendor/imgui/bin vendor/imgui/build
    rm Makefile
    rm LumaEditor/*.make
    rm Luma2D/Makefile
    rm vendor/imgui/Makefile
else
    system="$2"
    premake5 gmake
    make all config=$config -j7
fi
