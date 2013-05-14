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

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" ) # check if this works!
	add_definitions( -std=c++0x ) 
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# main options
SET( PROJECT_NAME "MapCity" )
SET( OUTPUT_NAME "mapcity" )

# set project name
project( ${PROJECT_NAME} )

# copy all executables to top build directory
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

file(COPY assets DESTINATION ${PROJECT_BINARY_DIR})

# add source directory
add_subdirectory( "src" )

# Doxygen
add_subdirectory( "doc" )
