# ==============================================================================
#
# AcceleratorEngine (ACE) CMakeLists.txt
# v0.0.1 by Jan Doerntlein 
#
# ==============================================================================
# Include library directories
include_directories(${ACE_SOURCE_DIR}/lib)
link_directories(${ACE_BINARY_DIR}/lib)

# ==============================================================================
# Create executable
add_executable(demo main.cpp)

# ==============================================================================
# Finally link executable
target_link_libraries(demo ace)
