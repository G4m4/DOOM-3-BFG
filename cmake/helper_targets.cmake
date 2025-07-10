# Interface targets for setting multiple properties at once depending on e.g.
# platform, etc. This is done here rather than globally through e.g. Cmake
# presets as it is mandatory for the projeect to build

add_library(neo_platform_definitions INTERFACE)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_SIMULATE_ID STREQUAL
                                               "MSVC"))
  target_link_libraries(neo_platform_definitions
                        INTERFACE neo_windows_definitions)
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID
                                                    STREQUAL "AppleClang"))
  # target_compile_definitions(neo_preprocessor_definitions INTERFACE)
endif()
