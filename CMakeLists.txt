cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(ZEngineDemo VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============================================================================
# Platform Detection and Macros
# =============================================================================

# Detect operating system
if(WIN32)
    set(Z_PLATFORM_WINDOWS TRUE)
    set(Z_PLATFORM_NAME "Windows")
    message(STATUS "Platform: Windows")
elseif(APPLE)
    set(Z_PLATFORM_MACOS TRUE)
    set(Z_PLATFORM_NAME "macOS")
    message(STATUS "Platform: macOS")
elseif(UNIX)
    set(Z_PLATFORM_LINUX TRUE)
    set(Z_PLATFORM_NAME "Linux")
    message(STATUS "Platform: Linux")
elseif(ANDROID)
    set(Z_PLATFORM_ANDROID TRUE)
    set(Z_PLATFORM_NAME "Android")
    message(STATUS "Platform: Android")
elseif(IOS)
    set(Z_PLATFORM_IOS TRUE)
    set(Z_PLATFORM_NAME "iOS")
    message(STATUS "Platform: iOS")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Detect architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(Z_ARCH_X64 TRUE)
    set(Z_ARCH_NAME "x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i[3-6]86")
    set(Z_ARCH_X86 TRUE)
    set(Z_ARCH_NAME "x86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
    set(Z_ARCH_ARM64 TRUE)
    set(Z_ARCH_NAME "ARM64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(Z_ARCH_ARM32 TRUE)
    set(Z_ARCH_NAME "ARM32")
else()
    set(Z_ARCH_NAME "Unknown")
    message(WARNING "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# Detect compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(Z_COMPILER_MSVC TRUE)
    set(Z_COMPILER_NAME "MSVC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(Z_COMPILER_GCC TRUE)
    set(Z_COMPILER_NAME "GCC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(Z_COMPILER_CLANG TRUE)
    set(Z_COMPILER_NAME "Clang")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(Z_COMPILER_APPLE_CLANG TRUE)
    set(Z_COMPILER_NAME "AppleClang")
else()
    set(Z_COMPILER_NAME "Unknown")
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Define platform macros for C++ code
if(Z_PLATFORM_WINDOWS)
    add_compile_definitions(
        Z_PLATFORM_WINDOWS=1
        Z_PLATFORM_WIN=1
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
elseif(Z_PLATFORM_ANDROID)
    add_compile_definitions(
        Z_PLATFORM_ANDROID=1
    )
elseif(Z_PLATFORM_MACOS)
    add_compile_definitions(
        Z_PLATFORM_MACOS=1
        Z_PLATFORM_MAC=1
    )
elseif(Z_PLATFORM_LINUX)
    add_compile_definitions(
        Z_PLATFORM_LINUX=1
    )
elseif(Z_PLATFORM_IOS)
    add_compile_definitions(
        Z_PLATFORM_IOS=1
    )
endif()

# Define architecture macros
if(Z_ARCH_X64)
    add_compile_definitions(Z_ARCH_X64=1)
    # Windows SDK requires _WIN64 and _AMD64_ for x64 builds
    if(Z_PLATFORM_WINDOWS)
        add_compile_definitions(_WIN64 _AMD64_)
    endif()
elseif(Z_ARCH_X86)
    add_compile_definitions(Z_ARCH_X86=1)
    # Windows SDK requires _X86_ for x86 builds
    if(Z_PLATFORM_WINDOWS)
        add_compile_definitions(_X86_)
    endif()
elseif(Z_ARCH_ARM64)
    add_compile_definitions(Z_ARCH_ARM64=1)
    # Windows SDK requires _WIN64 and _ARM64_ for ARM64 builds
    if(Z_PLATFORM_WINDOWS)
        add_compile_definitions(_WIN64 _ARM64_)
    endif()
elseif(Z_ARCH_ARM32)
    add_compile_definitions(Z_ARCH_ARM32=1)
    # Windows SDK requires _ARM_ for ARM32 builds
    if(Z_PLATFORM_WINDOWS)
        add_compile_definitions(_ARM_)
    endif()
endif()

# Define compiler macros
if(Z_COMPILER_MSVC)
    add_compile_definitions(Z_COMPILER_MSVC=1)
elseif(Z_COMPILER_GCC)
    add_compile_definitions(Z_COMPILER_GCC=1)
elseif(Z_COMPILER_CLANG)
    add_compile_definitions(Z_COMPILER_CLANG=1)
elseif(Z_COMPILER_APPLE_CLANG)
    add_compile_definitions(Z_COMPILER_APPLE_CLANG=1)
endif()

# Print platform information
message(STATUS "Platform: ${Z_PLATFORM_NAME}")
message(STATUS "Architecture: ${Z_ARCH_NAME}")
message(STATUS "Compiler: ${Z_COMPILER_NAME}")

# Set engine root path from environment variable
# ZENGINE_ROOT should be set via registry/environment variable
if(NOT DEFINED ZENGINE_ROOT)
    set(ZENGINE_ROOT $ENV{ZENGINE_ROOT})
endif()
if(NOT ZENGINE_ROOT)
    message(FATAL_ERROR "ZENGINE_ROOT environment variable is not set. Please set it to the engine root directory.")
endif()

# Set project root directory
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
# This will set PROJECT_HEADER_FILES variable needed for reflection code generation
add_subdirectory(source)

