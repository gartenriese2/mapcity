################################################################################
#
#	MapCity CMake files
#
################################################################################

# specify minimum cmake version
cmake_minimum_required( VERSION 2.8 )

# compiler stuff
if( APPLE )
	add_definitions( -std=c++11 )
endif( APPLE )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
	add_definitions( -std=c++0x )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# main options
SET( PROJECT_NAME "MapCity" )
SET( OUTPUT_NAME "mapcity" )

# set project name
project( ${PROJECT_NAME} )

# add source directory
add_subdirectory( "src" )

# Doxygen
add_subdirectory( "doc" )
