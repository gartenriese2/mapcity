cmake_minimum_required(VERSION 2.8.12)
project(mapcity)

#--------------------------------------------------------------------
# Set version
#--------------------------------------------------------------------
set(MAPCITY_VERSION_MAJOR "0")
set(MAPCITY_VERSION_MINOR "1")
set(MAPCITY_VERSION_PATCH "1")
set(MAPCITY_VERSION_EXTRA "-alpha")
set(MAPCITY_VERSION "${MAPCITY_VERSION_MAJOR}.${MAPCITY_VERSION_MINOR}")
set(MAPCITY_VERSION_FULL "${MAPCITY_VERSION}.${MAPCITY_VERSION_PATCH}${MAPCITY_VERSION_EXTRA}")
message("Version: ${MAPCITY_VERSION_FULL}")

set(CMAKE_BUILD_TYPE Release)

#--------------------------------------------------------------------
# Check OS
#--------------------------------------------------------------------
if (NOT UNIX)
	message(FATAL_ERROR "Only UNIX is supported so far!")
endif ()

#--------------------------------------------------------------------
# Set compiler specific flags
#--------------------------------------------------------------------
if (UNIX)
	set(MAPCITY_WARNING_FLAGS " -Wall -pedantic -Wextra -Werror -Wcast-align -Wconversion -Wfloat-equal -Wformat=2 -Wmissing-declarations -Woverlength-strings -Wshadow -Wunreachable-code")
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(MAPCITY_WARNING_FLAGS "${MAPCITY_WARNING_FLAGS} -Wimplicit-atomic-properties -Wstrict-selector-match -Wundeclared-selector")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	endif ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -msse2 -msse3 ${MAPCITY_WARNING_FLAGS}")
endif ()

#--------------------------------------------------------------------
# Glob files
#--------------------------------------------------------------------
file(GLOB_RECURSE CXX_SRCS src/*.cpp)
file(GLOB_RECURSE C_SRCS src/*.c)
file(GLOB_RECURSE HPP_HDRS src/*.hpp)
file(GLOB_RECURSE H_HDRS src/*.h)
set(SRCS "${C_SRCS};${CXX_SRCS}")
set(HDRS "${H_HDRS};${HPP_HDRS}")

#--------------------------------------------------------------------
# Find packages
#--------------------------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(Threads)

#--------------------------------------------------------------------
# MonoEngine
#--------------------------------------------------------------------
set(CONTRIB_DIR "${PROJECT_SOURCE_DIR}/contrib")

option(MONOENGINE_LEGACY "use legacy engine" OFF)
if (${MONOENGINE_LEGACY})
	set(MONOENGINE_BUILD_DIR "${PROJECT_SOURCE_DIR}/build/monoengine_legacy")
	set(MONOENGINE_DOWNLOAD_FILE "legacy.zip")
	add_definitions(-DLEGACY_MODE)
	set(MONOENGINE_DIR "${PROJECT_SOURCE_DIR}/contrib/monoengine_legacy")
else ()
	set(MONOENGINE_BUILD_DIR "${PROJECT_SOURCE_DIR}/build/monoengine")
	set(MONOENGINE_DOWNLOAD_FILE "master.zip")
	set(MONOENGINE_DIR "${PROJECT_SOURCE_DIR}/contrib/monoengine")
endif ()

set(MONOENGINE_LIB_NAME "libmonoEngine.a")

set(MONOENGINE_STAMP_DIR 		"${MONOENGINE_BUILD_DIR}/stamp")
set(MONOENGINE_TMP_DIR 			"${MONOENGINE_BUILD_DIR}/tmp")
set(MONOENGINE_DOWNLOAD_DIR 	"${PROJECT_SOURCE_DIR}/dl")
set(MONOENGINE_LIB_INSTALL_DIR 	"${MONOENGINE_BUILD_DIR}/libinstall")
set(MONOENGINE_LIB_DIR 			"${MONOENGINE_DIR}/lib")
set(MONOENGINE_SOURCE_DIR 		"${MONOENGINE_BUILD_DIR}/source")
set(MONOENGINE_INCLUDE_DIR 		"${MONOENGINE_DIR}/include")

set(MONOENGINE_CMAKE_ARGS -DSTATIC_LIB=1 -DGLFW_DOWNLOAD_DIR:STRING=${MONOENGINE_DOWNLOAD_DIR} -DCMAKE_INSTALL_PREFIX=${MONOENGINE_INSTALL_DIR})

if (EXISTS ${MONOENGINE_DOWNLOAD_DIR}/${MONOENGINE_DOWNLOAD_FILE})
	set(MONOENGINE_URL "${MONOENGINE_DOWNLOAD_DIR}/${MONOENGINE_DOWNLOAD_FILE}")
else ()
	set(MONOENGINE_URL "https://github.com/gartenriese2/monoengine/archive/${MONOENGINE_DOWNLOAD_FILE}")
endif ()

include(ExternalProject)
ExternalProject_Add(
	MonoEngine
	URL ${MONOENGINE_URL}
	TMP_DIR ${MONOENGINE_TMP_DIR}
	DOWNLOAD_DIR ${MONOENGINE_DOWNLOAD_DIR}
	STAMP_DIR ${MONOENGINE_STAMP_DIR}
	SOURCE_DIR ${MONOENGINE_SOURCE_DIR}
	BINARY_DIR ${MONOENGINE_LIB_INSTALL_DIR}
	INSTALL_DIR ${MONOENGINE_DIR}
	CMAKE_ARGS ${MONOENGINE_CMAKE_ARGS}
	INSTALL_COMMAND make
)
ExternalProject_Add_Step(
	MonoEngine
	createFolders
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES install
	COMMAND mkdir -p lib include/MonoEngine
	COMMENT "Creating MonoEngine folders"
)
ExternalProject_Add_Step(
	MonoEngine
	copySource
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES createFolders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${MONOENGINE_SOURCE_DIR}/src/engine ${MONOENGINE_INCLUDE_DIR}/MonoEngine
	COMMENT "Moving MonoEngine includes"
)
ExternalProject_Add_Step(
	MonoEngine
	copyContrib
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES createFolders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${MONOENGINE_SOURCE_DIR}/contrib ${CONTRIB_DIR}
	COMMENT "Moving MonoEngine contribs"
)
ExternalProject_Add_Step(
	MonoEngine
	copyLib
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES createFolders
	COMMAND mv ${MONOENGINE_LIB_INSTALL_DIR}/${MONOENGINE_LIB_NAME} ${MONOENGINE_LIB_DIR}
	COMMENT "Moving MonoEngine lib"
)

set(MONOENGINE_STATIC_LIB "${MONOENGINE_LIB_DIR}/${MONOENGINE_LIB_NAME}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${MONOENGINE_INCLUDE_DIR}")

#--------------------------------------------------------------------
# GLFW
#--------------------------------------------------------------------
set(GLFW_STATIC_LIB "${CONTRIB_DIR}/glfw/lib/libglfw3.a")
set(GLFW_LIBRARIES "-lX11 -lXrandr -lXi -lXxf86vm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${CONTRIB_DIR}/glfw/include")

#--------------------------------------------------------------------
# GLM
#--------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${CONTRIB_DIR}/glm")
add_definitions( -DGLM_FORCE_RADIANS )

#--------------------------------------------------------------------
# Building
#--------------------------------------------------------------------
add_executable(mapcity ${SRCS} ${HDRS})
target_link_libraries(mapcity ${MONOENGINE_STATIC_LIB} ${GLFW_STATIC_LIB} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(mapcity MonoEngine)
