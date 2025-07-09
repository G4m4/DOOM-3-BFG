# TypeInfo

add_executable(TypeInfo)

set(TYPEINFO_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(TypeInfo PRIVATE ${TYPEINFO_DIR})

set(TYPEINFOGEN_SRC
    main.cpp
    TypeInfoGen.cpp
    ${NEO_ROOT_DIR}/framework/CmdSystem.cpp
    ${NEO_ROOT_DIR}/framework/CVarSystem.cpp
    ${NEO_ROOT_DIR}/framework/File.cpp
    ${NEO_ROOT_DIR}/framework/File_Manifest.cpp
    ${NEO_ROOT_DIR}/framework/File_Resource.cpp
    ${NEO_ROOT_DIR}/framework/FileSystem.cpp
    ${NEO_ROOT_DIR}/sys/win32/win_cpu.cpp
    ${NEO_ROOT_DIR}/sys/win32/win_shared.cpp
    ${NEO_ROOT_DIR}/framework/Unzip.cpp)
set(TYPEINFOGEN_HDR
    TypeInfoGen.h
    ${NEO_ROOT_DIR}/framework/CmdSystem.h
    ${NEO_ROOT_DIR}/framework/CVarSystem.h
    ${NEO_ROOT_DIR}/framework/File.h
    ${NEO_ROOT_DIR}/framework/File_Manifest.h
    ${NEO_ROOT_DIR}/framework/File_Resource.h
    ${NEO_ROOT_DIR}/framework/FileSystem.h
    ${NEO_ROOT_DIR}/framework/Unzip.h
)

target_sources(TypeInfo PRIVATE ${TYPEINFOGEN_HDR} ${TYPEINFOGEN_SRC})

target_compile_definitions(TypeInfo PRIVATE ID_TYPEINFO)

target_precompile_headers(TypeInfo REUSE_FROM precompiled)
# dbghelp.lib is required for: __imp_UnDecorateSymbolName
# Winmm.lib is required for: __imp_timeGetTime
target_link_libraries(TypeInfo PRIVATE dbghelp.lib Winmm.lib externals
                                       neo_preprocessor_definitions idlib)
