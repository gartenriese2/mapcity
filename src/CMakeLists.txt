set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})

FILE(GLOB_RECURSE files "*.cpp" "*.hpp")

add_executable	( Main ${files} )

target_link_libraries(Main glfw GLEW GL rt)