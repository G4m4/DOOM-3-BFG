# Timidity static library target

add_library(timidity STATIC)

set(TIMIDITY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(timidity PRIVATE ${TIMIDITY_DIR})

set(TIMIDITY_HDR
    common.h
    config.h
    controls.h
    filter.h
    instrum.h
    mix.h
    output.h
    playmidi.h
    readmidi.h
    resample.h
    structs.h
    tables.h
    timidity.h
)
set(TIMIDITY_SRC
    common.cpp
    controls.cpp
    filter.cpp
    instrum.cpp
    mix.cpp
    output.cpp
    playmidi.cpp
    readmidi.cpp
    resample.cpp
    sdl_a.cpp
    sdl_c.cpp
    tables.cpp
    timidity.cpp
)

target_sources(timidity PRIVATE ${TIMIDITY_HDR} ${TIMIDITY_SRC})
