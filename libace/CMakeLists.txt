# ==============================================================================
#
# AcceleratorEngine (ACE) CMakeLists.txt
# v0.0.1 by Jan Doerntlein 
#
# ==============================================================================

# ==============================================================================
# Compiler stuff
add_definitions(-std=c++11)

# ==============================================================================
# create demo
add_subdirectory( "demo" )

# ==============================================================================
# copy assets directory
file(COPY "../assets" DESTINATION ${PROJECT_BINARY_DIR})

# copy shaders
file(COPY shader DESTINATION ${PROJECT_BINARY_DIR}/assets)

# ==============================================================================
# Required building dependencies
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

find_package( GLFW REQUIRED )

#if(APPLE)
	find_package(OpenGL REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
#endif(APPLE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
   MESSAGE("-- Configuring for Linux..." )
	find_package(GLEW REQUIRED)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# ==============================================================================
# Create Library
FILE(GLOB_RECURSE files "*.c" "*.cpp" "*.h")
FOREACH(item ${files})
  IF(${item} MATCHES "main.cpp")
    LIST(REMOVE_ITEM files ${item})
  ENDIF(${item} MATCHES "main.cpp")
ENDFOREACH(item)

# debug: print all files
FOREACH(item ${files})
	MESSAGE( "-- added " ${item})
ENDFOREACH(item)

# choose dynamic or static version
# add_library(ace STATIC ${files})
add_library(ace SHARED ${files})

# ==============================================================================
# Finally link executable
target_link_libraries(ace ${ASSIMP_LIBRARIES} glfw)

if(APPLE)
  target_link_libraries(ace ${OPENGL_LIBRARIES})
  Message( "-- Linking against " ${OPENGL_LIBRARIES})
  
  # GLFW doesn't run without these on OSX 10.7
  find_library(IOKit IOKit) 
  target_link_libraries(ace ${IOKit})
  Message( "-- Linking against " ${IOKit})

  find_library(Cocoa Cocoa)
  target_link_libraries(ace ${Cocoa})
  Message( "-- Linking against " ${Cocoa})

  target_link_libraries(ace ${CMAKE_SOURCE_DIR}/3rdparty/glfw-2.7.7/lib/cocoa/libglfw.a)
  target_link_libraries(ace ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif(APPLE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(ace ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
  #target_link_libraries(ace ${CMAKE_SOURCE_DIR}/3rdparty/glfw-2.7.7/lib/x11/libglfw.a)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
