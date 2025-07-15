# idlib static library target

add_library(idlib STATIC)

set(IDLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(
  idlib
  PUBLIC $<BUILD_INTERFACE:${IDLIB_DIR}>
  PRIVATE ${IDLIB_DIR})

set(IDLIB_SRC
    bv/Bounds.cpp
    bv/Box.cpp
    bv/Sphere.cpp
    CommandLink.cpp
    containers/HashIndex.cpp
    geometry/DrawVert.cpp
    geometry/JointTransform.cpp
    geometry/RenderMatrix.cpp
    geometry/Surface.cpp
    geometry/Surface_Patch.cpp
    geometry/Surface_Polytope.cpp
    geometry/Surface_SweptSpline.cpp
    geometry/TraceModel.cpp
    geometry/Winding.cpp
    geometry/Winding2D.cpp
    hashing/CRC32.cpp
    hashing/MD4.cpp
    hashing/MD5.cpp
    math/Angles.cpp
    math/Complex.cpp
    math/Lcp.cpp
    math/Math.cpp
    math/Matrix.cpp
    math/MatX.cpp
    math/Ode.cpp
    math/Plane.cpp
    math/Pluecker.cpp
    math/Polynomial.cpp
    math/Quat.cpp
    math/Rotation.cpp
    math/Simd.cpp
    math/Simd_Generic.cpp
    math/Simd_SSE.cpp
    math/Vector.cpp
    Base64.cpp
    CmdArgs.cpp
    Lexer.cpp
    math/VecX.cpp
    ParallelJobList.cpp
    Parser.cpp
    RectAllocator.cpp
    SoftwareCache.cpp
    Str.cpp
    sys/sys_assert.cpp
    Thread.cpp
    Token.cpp
    BitMsg.cpp
    Dict.cpp
    Heap.cpp
    LangDict.cpp
    Lib.cpp
    MapFile.cpp
    precompiled.cpp
    Timer.cpp)

set(IDLIB_HDR
    bv/Bounds.h
    bv/Box.h
    bv/Sphere.h
    Callback.h
    containers/Array.h
    containers/BinSearch.h
    containers/BTree.h
    containers/HashIndex.h
    containers/HashTable.h
    containers/Hierarchy.h
    containers/LinkList.h
    containers/List.h
    containers/PlaneSet.h
    containers/Queue.h
    containers/Sort.h
    containers/Stack.h
    containers/StaticList.h
    containers/StrList.h
    containers/StrPool.h
    containers/VectorSet.h
    DataQueue.h
    geometry/DrawVert.h
    geometry/DrawVert_intrinsics.h
    geometry/JointTransform.h
    geometry/RenderMatrix.h
    geometry/Surface.h
    geometry/Surface_Patch.h
    geometry/Surface_Polytope.h
    geometry/Surface_SweptSpline.h
    geometry/TraceModel.h
    geometry/Winding.h
    geometry/Winding2D.h
    hashing/CRC32.h
    hashing/MD4.h
    hashing/MD5.h
    math/Angles.h
    math/Complex.h
    math/Curve.h
    math/Extrapolate.h
    math/Interpolate.h
    math/Lcp.h
    math/Math.h
    math/Matrix.h
    math/MatX.h
    math/Ode.h
    math/Plane.h
    math/Pluecker.h
    math/Polynomial.h
    math/Quat.h
    math/Random.h
    math/Rotation.h
    math/Simd.h
    math/Simd_Generic.h
    math/Simd_SSE.h
    math/Vector.h
    Base64.h
    CmdArgs.h
    Lexer.h
    math/VecX.h
    ParallelJobList.h
    ParallelJobList_JobHeaders.h
    Parser.h
    SoftwareCache.h
    Str.h
    StrStatic.h
    Swap.h
    sys/sys_alloc_tags.h
    sys/sys_assert.h
    sys/sys_builddefines.h
    sys/sys_defines.h
    sys/sys_filesystem.h
    sys/sys_includes.h
    sys/sys_intrinsics.h
    sys/sys_threading.h
    sys/sys_types.h
    Thread.h
    Token.h
    BitMsg.h
    Dict.h
    Heap.h
    LangDict.h
    Lib.h
    MapFile.h
    precompiled.h
    Timer.h)

if(WIN32)
  list(APPEND IDLIB_SRC sys/win32/win_thread.cpp)
else()
  list(APPEND IDLIB_SRC sys/posix/posix_thread.cpp)
endif()

source_group(TREE "${IDLIB_DIR}" FILES ${IDLIB_SRC})

target_sources(idlib PRIVATE ${IDLIB_HDR} ${IDLIB_SRC})

target_compile_definitions(idlib PRIVATE __IDLIB__)

target_precompile_headers(idlib REUSE_FROM precompiled)
target_link_libraries(idlib PRIVATE OpenGL neo_platform_definitions)
