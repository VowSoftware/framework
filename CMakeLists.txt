# Not sure which minimum CMake version to use yet,
# so just choose a relatively modern version for now.
cmake_minimum_required(VERSION 3.24)

# Declare the project.
project(
    VowEngine
    VERSION 0.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://github.com/VowSoftware/vow-engine"
    LANGUAGES C)

# Determine if this is the top-level project,
# or if it's being built as a dependency to another project.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(VOWENGINE_STANDALONE ON)
else()
    set(VOWENGINE_STANDALONE OFF)
endif()

# Set language properties.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Include CMake module dependencies.
include(CMakeDependentOption)
include(CMakeOptions)

# Cache directory paths.
set(VOWENGINE_EXAMPLES "${CMAKE_CURRENT_LIST_DIR}/examples")
set(VOWENGINE_EXAMPLES_MAIN "${VOWENGINE_EXAMPLES}/main")
set(VOWENGINE_LIBS "${CMAKE_CURRENT_LIST_DIR}/libs")
set(VOWENGINE_LIBS_GLAD "${VOWENGINE_LIBS}/glad")
set(VOWENGINE_LIBS_GLFW "${VOWENGINE_LIBS}/glfw")
set(VOWENGINE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include")
set(VOWENGINE_INCLUDE_PUBLIC "${VOWENGINE_INCLUDE}/public")
set(VOWENGINE_INCLUDE_PRIVATE "${VOWENGINE_INCLUDE}/private")
set(VOWENGINE_SRC "${CMAKE_CURRENT_LIST_DIR}/src")

# Configure and build GLFW.
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC OFF)
add_subdirectory(${VOWENGINE_LIBS_GLFW})

# Cache source files.
set(VOWENGINE_SOURCES
    "${VOWENGINE_SRC}/log.c"
    "${VOWENGINE_SRC}/memory.c"
    "${VOWENGINE_SRC}/window.c")

# Declare as a static library.
add_library(
    ${CMAKE_PROJECT_NAME}
    STATIC
    ${VOWENGINE_SOURCES})

# Add the root directory of the header files as a standard include path.
# This allows source files to use `#include <vowengine/[path]>` to include engine headers.
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${VOWENGINE_INCLUDE_PUBLIC}
    PRIVATE
    ${VOWENGINE_INCLUDE_PRIVATE}
    "${VOWENGINE_LIBS_GLAD}/include")

# Link against third-party libraries.
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    glfw)

# Build example projects.
if(${VOWENGINE_BUILD_EXAMPLES})

    add_executable(example-window "${VOWENGINE_EXAMPLES}/window/window.c")
    target_link_libraries(example-window ${CMAKE_PROJECT_NAME})

endif()