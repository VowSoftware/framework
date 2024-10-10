# Set the build type for single-configuration generators.
set(CMAKE_BUILD_TYPE Debug CACHE STRING "CMake build type.")

# Option to build example projects.
# Only available if Vow Engine is the top-level project.
cmake_dependent_option(VOWENGINE_BUILD_EXAMPLES "Build Vow Engine example projects." ON "${VOWENGINE_STANDALONE}" OFF)