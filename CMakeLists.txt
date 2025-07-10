# DOOM3-BFG root cmake

cmake_minimum_required(VERSION 3.22)

project(doom3bfg)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/helper_targets.cmake)

set(DOOM_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# This is not ideal but idlib includes are required for the doomclassic target
set(NEO_ROOT_DIR ${DOOM_ROOT_DIR}/neo)

# DX SDK interface
message("DXSDK_DIR: $ENV{DXSDK_DIR}")
add_library(DirectXSDK INTERFACE)
target_include_directories(DirectXSDK INTERFACE $ENV{DXSDK_DIR}/include)
target_link_directories(DirectXSDK INTERFACE $ENV{DXSDK_DIR}/Lib/x64)
target_link_libraries(DirectXSDK INTERFACE X3DAudio xinput dinput8 dsound
                                           dxguid DxErr)

if(MSVC)
  # Common Windows PC target holding all Windows related quirkiness
  add_library(neo_windows_definitions INTERFACE)

  target_compile_definitions(
    neo_windows_definitions
    INTERFACE _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE
              NTDDI_VERSION=NTDDI_WIN7 WINVER=_WIN32_WINNT_WIN7
              _WIN32_WINNT=_WIN32_WINNT_WIN7)

  # dbghelp is required for: __imp_UnDecorateSymbolName winmm is required for:
  # __imp_timeGetTime
  target_link_libraries(
    neo_windows_definitions
    INTERFACE dbghelp
              glu32
              iphlpapi
              odbc32
              odbccp32
              opengl32
              winmm
              wsock32)
endif()

add_subdirectory(doomclassic)
add_subdirectory(neo)
