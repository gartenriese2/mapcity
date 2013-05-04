################################################################################
#
#	MapCity CMake files
#
################################################################################

# add externel cmake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

# check these!
find_package( GLM REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLFW REQUIRED )
find_package( GLEW REQUIRED )

include_directories( ${GLM_INCLUDE_DIRS} )

FILE( GLOB_RECURSE files "*.cpp" "*.hpp" )

add_executable( ${OUTPUT_NAME} ${files} )

# Linux
if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
	target_link_libraries( ${OUTPUT_NAME} glfw GLEW GL rt)
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# Mac OSX
if( APPLE )
	include_directories( ${OPENGL_INCLUDE_DIRS} )
	target_link_libraries( ${OUTPUT_NAME} ${OPENGL_LIBRARIES} )

	# GLFW doesn't run without these on OSX 10.7
	find_library( IOKit IOKit ) 
	target_link_libraries( ${OUTPUT_NAME} ${IOKit} )
	Message( "-- Linking against " ${IOKit} )

	find_library( Cocoa Cocoa )
	target_link_libraries( ${OUTPUT_NAME} ${Cocoa} )
	Message( "-- Linking against " ${Cocoa} )

    target_link_libraries( ${OUTPUT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glfw )
endif( APPLE )
