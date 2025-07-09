# DOOM3-BFG root cmake

cmake_minimum_required(VERSION 3.22)

project(neo)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# PCH
set(ID_PRECOMPILED_HEADERS "idlib/precompiled.h")
add_library(precompiled)
target_sources(precompiled PRIVATE "idlib/precompiled.cpp")
target_precompile_headers(precompiled PUBLIC ${ID_PRECOMPILED_HEADERS})

add_subdirectory(idlib)
add_subdirectory(d3xp)
