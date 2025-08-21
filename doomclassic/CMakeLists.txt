# Doom Classic static library target

add_library(doomclassic STATIC)

set(DOOMCLASSIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(
  doomclassic
  PUBLIC ${DOOMCLASSIC_DIR}
  PRIVATE ${DOOMCLASSIC_DIR} ${NEO_ROOT_DIR})

# There is a custom precompield header for this one
set(DOOMCLASSIC_PRECOMPILED_HEADERS "${DOOMCLASSIC_DIR}/doom/Precompiled.h")
add_library(doomclassic_precompiled STATIC)
target_include_directories(doomclassic_precompiled PRIVATE ${DOOMCLASSIC_DIR}
                                                           ${NEO_ROOT_DIR})
target_sources(doomclassic_precompiled
               PRIVATE "${DOOMCLASSIC_DIR}/doom/Precompiled.cpp")
target_precompile_headers(doomclassic_precompiled PUBLIC
                          ${DOOMCLASSIC_PRECOMPILED_HEADERS})
target_link_libraries(doomclassic_precompiled PRIVATE neo_platform_definitions)

set(DOOMCLASSIC_SRC
    doom/am_map.cpp
    doom/doominterface.cpp
    doom/doomlib.cpp
    doom/dstrings.cpp
    doom/d_items.cpp
    doom/d_main.cpp
    doom/d_net.cpp
    doom/f_finale.cpp
    doom/f_wipe.cpp
    doom/globaldata.cpp
    doom/g_game.cpp
    doom/hu_lib.cpp
    doom/hu_stuff.cpp
    doom/info.cpp
    doom/i_input.cpp
    doom/i_system.cpp
    doom/i_video_ps3.cpp
    doom/mus2midi.cpp
    doom/m_argv.cpp
    doom/m_bbox.cpp
    doom/m_cheat.cpp
    doom/m_fixed.cpp
    doom/m_menu.cpp
    doom/m_misc.cpp
    doom/m_random.cpp
    doom/p_ceilng.cpp
    doom/p_doors.cpp
    doom/p_enemy.cpp
    doom/p_floor.cpp
    doom/p_inter.cpp
    doom/p_lights.cpp
    doom/p_map.cpp
    doom/p_maputl.cpp
    doom/p_mobj.cpp
    doom/p_plats.cpp
    doom/p_pspr.cpp
    doom/p_saveg.cpp
    doom/p_setup.cpp
    doom/p_sight.cpp
    doom/p_spec.cpp
    doom/p_switch.cpp
    doom/p_telept.cpp
    doom/p_tick.cpp
    doom/p_user.cpp
    doom/r_bsp.cpp
    doom/r_data.cpp
    doom/r_draw.cpp
    doom/r_main.cpp
    doom/r_plane.cpp
    doom/r_segs.cpp
    doom/r_sky.cpp
    doom/r_things.cpp
    doom/sounds.cpp
    doom/st_lib.cpp
    doom/st_stuff.cpp
    doom/s_sound.cpp
    doom/tables.cpp
    doom/v_video.cpp
    doom/wi_stuff.cpp
    doom/w_wad.cpp
    doom/z_zone.cpp)

set(DOOMCLASSIC_HDR
    doom/am_map.h
    doom/constructs.h
    doom/defs.h
    doom/doomdata.h
    doom/doomdef.h
    doom/doominterface.h
    doom/doomlib.h
    doom/doomstat.h
    doom/doomtype.h
    doom/dstrings.h
    doom/d_englsh.h
    doom/d_event.h
    doom/d_french.h
    doom/d_items.h
    doom/d_main.h
    doom/d_net.h
    doom/d_player.h
    doom/d_textur.h
    doom/d_think.h
    doom/d_ticcmd.h
    doom/f_finale.h
    doom/f_wipe.h
    doom/globaldata.h
    doom/g_game.h
    doom/hu_lib.h
    doom/hu_stuff.h
    doom/info.h
    doom/i_net.h
    doom/i_sound.h
    doom/i_system.h
    doom/i_video.h
    doom/m_argv.h
    doom/m_bbox.h
    doom/m_cheat.h
    doom/m_fixed.h
    doom/m_menu.h
    doom/m_misc.h
    doom/m_random.h
    doom/m_swap.h
    doom/p_inter.h
    doom/p_local.h
    doom/p_mobj.h
    doom/p_pspr.h
    doom/p_saveg.h
    doom/p_setup.h
    doom/p_spec.h
    doom/p_tick.h
    doom/r_bsp.h
    doom/r_data.h
    doom/r_defs.h
    doom/r_draw.h
    doom/r_local.h
    doom/r_main.h
    doom/r_plane.h
    doom/r_segs.h
    doom/r_sky.h
    doom/r_state.h
    doom/r_things.h
    doom/sounds.h
    doom/structs.h
    doom/st_lib.h
    doom/st_stuff.h
    doom/s_sound.h
    doom/tables.h
    doom/typedefs.h
    doom/vars.h
    doom/v_video.h
    doom/wi_stuff.h
    doom/w_wad.h
    doom/z_zone.h)

if(WIN32)
  list(
    APPEND
    DOOMCLASSIC_SRC
    doom/i_net_win32.cpp
    doom/i_sound_win32.cpp
  )
else()
  list(
    APPEND
    DOOMCLASSIC_SRC
  )
endif()

target_sources(doomclassic PRIVATE ${DOOMCLASSIC_HDR} ${DOOMCLASSIC_SRC})

target_compile_definitions(doomclassic
                           PRIVATE _LIB _D3XP;CTF;_CRT_SECURE_NO_DEPRECATE)

target_link_libraries(doomclassic PRIVATE DirectXSDK neo_platform_definitions)
target_precompile_headers(doomclassic REUSE_FROM doomclassic_precompiled)

add_subdirectory(timidity)
