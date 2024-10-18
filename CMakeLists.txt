# Not sure which minimum CMake version to use yet,
# so just choose a relatively modern version for now.
cmake_minimum_required(VERSION 3.24)

# Declare the project.
project(
    VowFramework
    VERSION 0.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://github.com/VowSoftware/framework"
    LANGUAGES C)

# Determine if this is the top-level project,
# or if it's being built as a dependency to another project.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(VOW_STANDALONE ON)
else()
    set(VOW_STANDALONE OFF)
endif()

# Set language properties.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Include the `cmake_dependent_option()` function.
include(CMakeDependentOption)

# Set the build type for single-configuration generators.
set(CMAKE_BUILD_TYPE Debug CACHE STRING "CMake build type.")

# Option to build example projects.
# Only available if Vow Framework is the top-level project.
cmake_dependent_option(VOW_BUILD_EXAMPLES "Build Vow Framework example projects." ON "${VOW_STANDALONE}" OFF)

# Maximum amount of each resource type.
set(VOW_SHADER_CAPACITY 100 CACHE STRING "Maximum amount of shaders.")
set(VOW_TIMER_CAPACITY 1000 CACHE STRING "Maximum amount of timers.")

# Cache directory paths.
set(VOW_EXAMPLES "${CMAKE_CURRENT_LIST_DIR}/examples")
set(VOW_EXAMPLES_MAIN "${VOW_EXAMPLES}/main")
set(VOW_DEPENDENCIES "${CMAKE_CURRENT_LIST_DIR}/dependencies")
set(VOW_DEPENDENCIES_GLAD "${VOW_DEPENDENCIES}/glad")
set(VOW_DEPENDENCIES_GLFW "${VOW_DEPENDENCIES}/glfw")
set(VOW_HEADERS "${CMAKE_CURRENT_LIST_DIR}/headers")
set(VOW_HEADERS_PUBLIC "${VOW_HEADERS}/public")
set(VOW_HEADERS_PRIVATE "${VOW_HEADERS}/private")
set(VOW_SOURCES "${CMAKE_CURRENT_LIST_DIR}/sources")

# Configure and build GLFW.
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC OFF)
add_subdirectory(${VOW_DEPENDENCIES_GLFW})

# Cache source files.
set(VOW_SOURCES
    "${VOW_SOURCES}/file.c"
    "${VOW_SOURCES}/framework.c"
    "${VOW_SOURCES}/log.c"
    "${VOW_SOURCES}/memory.c"
    "${VOW_SOURCES}/shader.c"
    "${VOW_SOURCES}/timer.c"
    "${VOW_SOURCES}/tuple.c"
    "${VOW_SOURCES}/window.c")

# Declare as a static library.
add_library(
    ${CMAKE_PROJECT_NAME}
    STATIC
    ${VOW_SOURCES})

# Add the root directory of the header files as a standard include path.
# This allows source files to use `#include <vowframework/[path]>` to include framework headers.
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${VOW_HEADERS_PUBLIC}
    PRIVATE
    ${VOW_HEADERS_PRIVATE}
    "${VOW_DEPENDENCIES_GLAD}/include")

# Link against third-party libraries.
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    glfw)

target_compile_definitions(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    VOW_SHADER_CAPACITY=${VOW_SHADER_CAPACITY}
    VOW_TIMER_CAPACITY=${VOW_TIMER_CAPACITY})

# Build example projects.
if(${VOW_BUILD_EXAMPLES})

    add_executable(example-window "${VOW_EXAMPLES}/window/window.c")
    target_link_libraries(example-window ${CMAKE_PROJECT_NAME})

endif()