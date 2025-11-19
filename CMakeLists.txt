cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(ZEngineDemo VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set engine root path from environment variable
# ZENGINE_ROOT should be set via registry/environment variable
if(NOT DEFINED ZENGINE_ROOT)
    set(ZENGINE_ROOT $ENV{ZENGINE_ROOT})
endif()
if(NOT ZENGINE_ROOT)
    message(FATAL_ERROR "ZENGINE_ROOT environment variable is not set. Please set it to the engine root directory.")
endif()

# Configure ZEngine unified output directory
# This ensures all projects use the same engine build outputs
# Set this to the same value as ZENGINE_ROOT/bin to share builds
if(NOT DEFINED ZENGINE_UNIFIED_OUTPUT_DIR)
    set(ZENGINE_UNIFIED_OUTPUT_DIR "${ZENGINE_ROOT}/bin" CACHE PATH "Unified output directory for ZEngine libraries")
endif()

# Add engine as subdirectory
# The engine's CMakeLists.txt is configured to output all libraries to
# ZENGINE_UNIFIED_OUTPUT_DIR, so multiple projects can share the same build
if(EXISTS "${ZENGINE_ROOT}/CMakeLists.txt")
    message(STATUS "Including ZEngine from ${ZENGINE_ROOT}")
    message(STATUS "Engine libraries will be output to: ${ZENGINE_UNIFIED_OUTPUT_DIR}")
    add_subdirectory(${ZENGINE_ROOT} ${CMAKE_BINARY_DIR}/engine)
else()
    message(FATAL_ERROR "Cannot find ZEngine at ${ZENGINE_ROOT}. Please set ZENGINE_ROOT environment variable.")
endif()

# Add project source directory
add_subdirectory(source)
