################################################################################
#
#	MapCity CMake files
#
################################################################################

# specify minimum cmake version
cmake_minimum_required( VERSION 2.8 )

# add cmake modules
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules;${CMAKE_MODULE_PATH}")

# main options
SET( PROJECT_NAME "MapCity" )
SET( OUTPUT_NAME "mapcity" )

# set project name
project( ${PROJECT_NAME} )

# copy all executables to top build directory
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

# compiler stuff
add_definitions( -std=c++11 -g )#-Wall -Wextra -Werror -pedantic -Wno-unused-value -Wno-unused-parameter -no-unused-function -Wuninitialized -Wshadow -Wconversion -Wswitch-default -Winit-self -Wunreachable-code)

# add source directory
add_subdirectory( "src" )

# Doxygen
add_subdirectory( "doc" )
