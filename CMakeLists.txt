cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(ZEngineDemo VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set engine root path
set(ZENGINE_ROOT "E:/ZEngine")

# Add engine as subdirectory
# Note: This assumes the engine is built alongside the project.
# If you prefer to use a pre-built engine, modify this section.
if(EXISTS "${ZENGINE_ROOT}/CMakeLists.txt")
    add_subdirectory(${ZENGINE_ROOT} ${CMAKE_BINARY_DIR}/engine)
else()
    message(FATAL_ERROR "Cannot find ZEngine at ${ZENGINE_ROOT}. Please set ZENGINE_ROOT environment variable.")
endif()

# Add project source directory
add_subdirectory(source)
