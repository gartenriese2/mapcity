cmake_minimum_required(VERSION 2.8.0)

project(mapcity)
set(CMAKE_BUILD_TYPE Release)

# warnings
set(MY_WARNING_FLAGS " -Wall -pedantic -Wextra -Werror -Wcast-align -Wconversion -Wfloat-equal -Wformat=2 -Wimplicit-atomic-properties -Wmissing-declarations -Woverlength-strings -Wshadow -Wstrict-selector-match -Wundeclared-selector -Wunreachable-code ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -msse2 -msse3 ${MY_WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-omit-frame-pointer")
add_definitions( -I${PROJECT_SOURCE_DIR}/src )

#
# Files
#
file(GLOB_RECURSE CXX_SRCS src/*.cpp)
file(GLOB_RECURSE C_SRCS src/*.c)
file(GLOB_RECURSE HDRS1 src/*.h)
file(GLOB_RECURSE HDRS1 src/*.hpp)
set(SRCS "${C_SRCS};${CXX_SRCS}")
set(HDRS "${HDRS1};${HDRS2}")

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads)

# monoEngine
set(MONOENGINE_PREFIX "${PROJECT_SOURCE_DIR}/contrib/monoengine")
set(MONOENGINE_INSTALL_DIR "${PROJECT_SOURCE_DIR}/contrib/monoengine")
set(MONOENGINE_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${MONOENGINE_INSTALL_DIR})

include(ExternalProject)
ExternalProject_Add(
	MonoEngine
	PREFIX ${MONOENGINE_PREFIX}
	URL https://github.com/gartenriese2/monoengine/archive/v1.0.3-static-lib.zip
	INSTALL_DIR ${MONOENGINE_INSTALL_DIR}
	CMAKE_ARGS ${MONOENGINE_CMAKE_ARGS}
	INSTALL_COMMAND make
)
set(MONOENGINE_STATIC_LIB "${MONOENGINE_INSTALL_DIR}/src/MonoEngine-build/libMonoEngine.a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${MONOENGINE_INSTALL_DIR}/src/")

set(GLFW_STATIC_LIB "${MONOENGINE_INSTALL_DIR}/src/MonoEngine/contrib/glfw/lib/libglfw3.a")
set(GLFW_LIBRARIES "-lX11 -lXrandr -lXi -lXxf86vm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${MONOENGINE_INSTALL_DIR}/src/MonoEngine/contrib/glfw/include")

# glm
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${PROJECT_SOURCE_DIR}/contrib/glm")
add_definitions( -DGLM_FORCE_RADIANS )

add_executable(mapcity ${SRCS} ${HDRS})

target_link_libraries(mapcity ${MONOENGINE_STATIC_LIB} ${GLFW_STATIC_LIB} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
