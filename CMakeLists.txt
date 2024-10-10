cmake_minimum_required(VERSION 3.24)

project(
    VowEngine
    VERSION 0.0.0
    DESCRIPTION ""
    HOMEPAGE_URL "https://github.com/VowSoftware/vow-engine"
    LANGUAGES C)

# Determine if Vow Engine is the top-level project,
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

include(CMakeDependentOption)
include(CMakeOptions)

# Cache directory paths.
set(VOWENGINE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include")
set(VOWENGINE_SRC "${CMAKE_CURRENT_LIST_DIR}/src")
set(VOWENGINE_EXAMPLES "${CMAKE_CURRENT_LIST_DIR}/examples")

set(VOWENGINE_HEADERS
    "${VOWENGINE_INCLUDE}/vowengine/memory.h")

set(VOWENGINE_SOURCES
    "${VOWENGINE_SRC}/memory.c")

# Declare Vow Engine as a static library.
add_library(
    ${CMAKE_PROJECT_NAME}
    STATIC
    ${VOWENGINE_SOURCES})

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${VOWENGINE_INCLUDE})

# Build example projects.
if(${VOWENGINE_BUILD_EXAMPLES})

    add_executable(example-main "${VOWENGINE_EXAMPLES}/main/main.c")
    target_link_libraries(example-main ${CMAKE_PROJECT_NAME})

endif()