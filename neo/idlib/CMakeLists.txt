# idlib static library target

add_library(idlib STATIC)

set(IDLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(
  idlib
  PUBLIC $<BUILD_INTERFACE:${IDLIB_DIR}>
  PRIVATE ${IDLIB_DIR})

file(GLOB_RECURSE IDLIB_SRC ${IDLIB_DIR}/*.cpp)
source_group(TREE "${IDLIB_DIR}" FILES ${IDLIB_SRC})
file(GLOB_RECURSE IDLIB_HDR ${IDLIB_DIR}/*.h)

target_sources(idlib PRIVATE ${IDLIB_HDR} ${IDLIB_SRC})

target_compile_definitions(idlib PRIVATE __IDLIB__)

target_precompile_headers(idlib REUSE_FROM precompiled)
target_link_libraries(idlib PRIVATE neo_platform_definitions)
