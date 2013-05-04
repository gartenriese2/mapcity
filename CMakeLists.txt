#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

#Name your project here
project(MapCity)

add_subdirectory ( "src" )