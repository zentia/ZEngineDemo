# Reflection code generation configuration for ZEngineDemo
# This file configures ZParser to generate reflection code for serialization support

# Set paths for precompile tools
set(PRECOMPILE_TOOLS_PATH "${ZENGINE_ROOT}/bin")
set(Z_PRECOMPILE_PARAMS_IN_PATH "${PROJECT_ROOT_DIR}/precompile.json.in")
set(Z_PRECOMPILE_PARAMS_PATH "${CMAKE_BINARY_DIR}/precompile.json")
configure_file(${Z_PRECOMPILE_PARAMS_IN_PATH} ${Z_PRECOMPILE_PARAMS_PATH})

# Configure parser executable based on platform
if(CMAKE_HOST_WIN32)
    set(PRECOMPILE_PARSER ${PRECOMPILE_TOOLS_PATH}/ZParser.exe)
    set(sys_include "*")
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(PRECOMPILE_PARSER ${PRECOMPILE_TOOLS_PATH}/ZParser)
    set(sys_include "/usr/include/c++/9/")
elseif(CMAKE_HOST_APPLE)
    find_program(XCRUN_EXECUTABLE xcrun)
    if(NOT XCRUN_EXECUTABLE)
        message(FATAL_ERROR "xcrun not found!!!")
    endif()
    execute_process(
        COMMAND ${XCRUN_EXECUTABLE} --sdk macosx --show-sdk-platform-path
        OUTPUT_VARIABLE osx_sdk_platform_path_test
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(PRECOMPILE_PARSER ${PRECOMPILE_TOOLS_PATH}/ZParser)
    set(sys_include "${osx_sdk_platform_path_test}/../../Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1")
endif()

# Set parser input file
set(PARSER_INPUT ${CMAKE_BINARY_DIR}/parser_header.h)

# Create stamp file for dependency tracking
set(PRECOMPILE_STAMP ${CMAKE_BINARY_DIR}/.precompile_stamp)

# Custom command to run meta parser
add_custom_command(
    OUTPUT ${PRECOMPILE_STAMP}
    BYPRODUCTS ${PARSER_INPUT}
    DEPENDS ${Z_PRECOMPILE_PARAMS_PATH} $<TARGET_FILE:ZParser>
    COMMENT "Running meta parser for ZEngineDemo reflection code generation"
    COMMAND
        ${CMAKE_COMMAND} -E echo "[Precompile] Generating reflection code for ZEngineDemo..."
    COMMAND
        ${PRECOMPILE_PARSER} "${Z_PRECOMPILE_PARAMS_PATH}" "${PARSER_INPUT}" "${PROJECT_ROOT_DIR}/source" ${sys_include} "ZEngineDemo" 0
    COMMAND
        ${CMAKE_COMMAND} -E touch ${PRECOMPILE_STAMP}
)

# Create target for reflection code generation
add_custom_target(${PROJECT_PRECOMPILE_TARGET} ALL
    DEPENDS ${PRECOMPILE_STAMP}
    COMMENT "Meta parser code generation target for ZEngineDemo"
)
