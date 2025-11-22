# ZEngineDemo source Directory
# This file manages all game modules

# Collect header files for reflection code generation
# This is used by the meta parser to generate reflection code
file(GLOB_RECURSE PROJECT_HEADER_FILES CONFIGURE_DEPENDS "*.h" "*.inl")
set(PROJECT_HEADER_FILES ${PROJECT_HEADER_FILES} PARENT_SCOPE)

# Add game modules
add_subdirectory(ZEngineDemo)

# Add more modules here as your project grows
# add_subdirectory(AnotherModule)
