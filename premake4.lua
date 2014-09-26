solution "mapcity"
    configurations {"Debug", "Release"}
    platforms {"Native"}

project "main"
    configurations {"Debug", "Release"}
    platforms {"Native"}
    kind "ConsoleApp"
    language "C++"

    location "./build"
    targetdir "./bin"
    targetname "mapcity"

    files {"src/**.h", "src/**.hpp", "src/**.cpp"}

    flags {"Symbols"}
    buildoptions {"-std=c++1y", "-Wall", "-pedantic", "-Wextra", "-Werror", "-Wno-unused-value",
        "-Wno-unused-parameter", "-Wno-unused-function", "-Wuninitialized", "-Wshadow",
        "-Wconversion", "-Wswitch-default", "-Winit-self", "-Wunreachable-code"}
    links {"glfw3", "pthread", "X11", "Xrandr", "Xxf86vm", "Xi", "GL", "GLEW"}

    buildoptions {"-stdlib=libc++"}
    linkoptions {"-stdlib=libc++"}
    links {"c++abi"}
    premake.gcc.cc = "clang"
    premake.gcc.cxx = "clang++"

    configuration "Debug"
        defines {"DEBUG"}

    configuration "Release"
        defines {"NDEBUG"}
        flags {"EnableSSE2", "OptimizeSpeed"}

