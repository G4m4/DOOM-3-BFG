include(cmake/cpm.cmake)

# Done as a function so that updates to variables like CMAKE_CXX_FLAGS don't
# propagate out to other targets
function(setup_dependencies)

  # Here we create interface targets holding dependencies including
  # configurations etc. These targets still exist but stay empty on platforms
  # not using them

  # Audio backends

  add_library(FAudio INTERFACE)
  if(UNIX)
    find_package(SDL3 REQUIRED)
    # FAudio
    cpmaddpackage(
      GITHUB_REPOSITORY
      FNA-XNA/FAudio
      GIT_TAG
      25.07
      OPTIONS
      "BUILD_SDL3 ON"
      "PLATFORM_WIN32 ${WIN32}"
      "XNASONG OFF")
    target_link_libraries(FAudio INTERFACE FAudio-shared)
  endif()

  # Rendering backends

  # DirectX - includes xaudio
  add_library(DirectXSDK INTERFACE)
  if(WIN32)
    message("DXSDK_DIR: $ENV{DXSDK_DIR}")
    target_include_directories(DirectXSDK INTERFACE $ENV{DXSDK_DIR}/include)
    target_link_directories(DirectXSDK INTERFACE $ENV{DXSDK_DIR}/Lib/x64)
    target_link_libraries(DirectXSDK INTERFACE X3DAudio xinput dinput8 dsound
                                               dxguid DxErr)
  endif()

  # OpenGL
  add_library(OpenGL INTERFACE)
  if(UNIX)
    find_package(OpenGL REQUIRED)
    if(OPENGL_FOUND)
      target_include_directories(OpenGL INTERFACE ${OPENGL_INCLUDE_DIR})
      target_link_libraries(OpenGL INTERFACE ${OPENGL_LIBRARIES})
    endif()
  endif()
endfunction()

# CPM licenses target here
cpm_licenses_create_disclaimer_target(
  write-licenses "${CMAKE_BINARY_SOURCE_DIR}/third_party.txt" "${CPM_PACKAGES}")
