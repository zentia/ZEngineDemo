# ZEngineDemo Module
# This is your game module, similar to Unreal Engine's game modules

set(TARGET_NAME ZEngineDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# source files
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "*.h" "*.inl")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp")

# Organize files
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

# Create library
add_library(${TARGET_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Game")

# Link to engine runtime
target_link_libraries(${TARGET_NAME} PUBLIC ZRuntime)

# Include directories
target_include_directories(${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
