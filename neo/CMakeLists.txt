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

add_subdirectory(d3xp)
add_subdirectory(idlib)

# External library

set(NEO_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(EXTERNALS_SRC
    framework/zlib/adler32.c
    framework/zlib/compress.c
    framework/zlib/crc32.c
    framework/zlib/deflate.c
    framework/zlib/gzio.c
    framework/zlib/infback.c
    framework/zlib/inffast.c
    framework/zlib/inflate.c
    framework/zlib/inftrees.c
    framework/zlib/trees.c
    framework/zlib/uncompr.c
    framework/zlib/zutil.c
    renderer/jpeg-6/jcapimin.cpp
    renderer/jpeg-6/jccoefct.cpp
    renderer/jpeg-6/jccolor.cpp
    renderer/jpeg-6/jcdctmgr.cpp
    renderer/jpeg-6/jchuff.cpp
    renderer/jpeg-6/jcinit.cpp
    renderer/jpeg-6/jcmainct.cpp
    renderer/jpeg-6/jcmarker.cpp
    renderer/jpeg-6/jcmaster.cpp
    renderer/jpeg-6/jcomapi.cpp
    renderer/jpeg-6/jcparam.cpp
    renderer/jpeg-6/jcphuff.cpp
    renderer/jpeg-6/jcprepct.cpp
    renderer/jpeg-6/jcsample.cpp
    renderer/jpeg-6/jdapimin.cpp
    renderer/jpeg-6/jdapistd.cpp
    renderer/jpeg-6/jdatadst.cpp
    renderer/jpeg-6/jdatasrc.cpp
    renderer/jpeg-6/jdcoefct.cpp
    renderer/jpeg-6/jdcolor.cpp
    renderer/jpeg-6/jddctmgr.cpp
    renderer/jpeg-6/jdhuff.cpp
    renderer/jpeg-6/jdinput.cpp
    renderer/jpeg-6/jdmainct.cpp
    renderer/jpeg-6/jdmarker.cpp
    renderer/jpeg-6/jdmaster.cpp
    renderer/jpeg-6/jdmerge.cpp
    renderer/jpeg-6/jdphuff.cpp
    renderer/jpeg-6/jdpostct.cpp
    renderer/jpeg-6/jdsample.cpp
    renderer/jpeg-6/jdtrans.cpp
    renderer/jpeg-6/jerror.cpp
    renderer/jpeg-6/jfdctflt.cpp
    renderer/jpeg-6/jfdctfst.cpp
    renderer/jpeg-6/jfdctint.cpp
    renderer/jpeg-6/jidctflt.cpp
    renderer/jpeg-6/jidctfst.cpp
    renderer/jpeg-6/jidctint.cpp
    renderer/jpeg-6/jidctred.cpp
    renderer/jpeg-6/jmemmgr.cpp
    renderer/jpeg-6/jmemnobs.cpp
    renderer/jpeg-6/jquant1.cpp
    renderer/jpeg-6/jquant2.cpp
    renderer/jpeg-6/jutils.cpp)
set(EXTERNALS_HDR
    renderer/jpeg-6/jchuff.h
    renderer/jpeg-6/jconfig.h
    renderer/jpeg-6/jdct.h
    renderer/jpeg-6/jdhuff.h
    renderer/jpeg-6/jerror.h
    renderer/jpeg-6/jinclude.h
    renderer/jpeg-6/jmemsys.h
    renderer/jpeg-6/jmorecfg.h
    renderer/jpeg-6/jpegint.h
    renderer/jpeg-6/jpeglib.h
    renderer/jpeg-6/jversion.h)

add_library(externals STATIC)
target_include_directories(externals PRIVATE ${NEO_ROOT_DIR}/renderer/jpeg-6)
target_sources(externals PRIVATE ${EXTERNALS_HDR} ${EXTERNALS_SRC})

target_compile_definitions(externals PRIVATE _LIB _D3XP)
