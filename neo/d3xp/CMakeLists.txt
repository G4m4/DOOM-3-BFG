# Game lib library target

add_library(gamed3xp STATIC)

set(GAMED3XP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(
  gamed3xp
  PUBLIC $<BUILD_INTERFACE:${GAMED3XP_DIR}>
  PRIVATE ${GAMED3XP_DIR})

set(GAMED3XP_SRC
    Achievements.cpp
    AimAssist.cpp
    ai/AAS.cpp
    ai/AAS_debug.cpp
    ai/AAS_pathing.cpp
    ai/AAS_routing.cpp
    ai/AI.cpp
    ai/AI_events.cpp
    ai/AI_pathing.cpp
    ai/AI_Vagary.cpp
    anim/Anim.cpp
    anim/Anim_Blend.cpp
    anim/Anim_Testmodel.cpp
    gamesys/Class.cpp
    gamesys/Event.cpp
    gamesys/SaveGame.cpp
    gamesys/SysCmds.cpp
    gamesys/SysCvar.cpp
    Leaderboards.cpp
    menus/MenuHandler.cpp
    menus/MenuHandler_HUD.cpp
    menus/MenuHandler_PDA.cpp
    menus/MenuHandler_Scoreboard.cpp
    menus/MenuHandler_Shell.cpp
    menus/MenuScreen.cpp
    menus/MenuScreen_HUD.cpp
    menus/MenuScreen_PDA_Inventory.cpp
    menus/MenuScreen_PDA_UserData.cpp
    menus/MenuScreen_PDA_UserEmails.cpp
    menus/MenuScreen_PDA_VideoDisks.cpp
    menus/MenuScreen_Scoreboard.cpp
    menus/MenuScreen_Shell_Bindings.cpp
    menus/MenuScreen_Shell_Browser.cpp
    menus/MenuScreen_Shell_ControllerLayout.cpp
    menus/MenuScreen_Shell_Controls.cpp
    menus/MenuScreen_Shell_Credits.cpp
    menus/MenuScreen_Shell_Dev.cpp
    menus/MenuScreen_Shell_Difficulty.cpp
    menus/MenuScreen_Shell_GameLobby.cpp
    menus/MenuScreen_Shell_GameOptions.cpp
    menus/MenuScreen_Shell_Gamepad.cpp
    menus/MenuScreen_Shell_Leaderboards.cpp
    menus/MenuScreen_Shell_Load.cpp
    menus/MenuScreen_Shell_MatchSettings.cpp
    menus/MenuScreen_Shell_ModeSelect.cpp
    menus/MenuScreen_Shell_NewGame.cpp
    menus/MenuScreen_Shell_PartyLobby.cpp
    menus/MenuScreen_Shell_Pause.cpp
    menus/MenuScreen_Shell_Playstation.cpp
    menus/MenuScreen_Shell_PressStart.cpp
    menus/MenuScreen_Shell_Resolution.cpp
    menus/MenuScreen_Shell_Root.cpp
    menus/MenuScreen_Shell_Save.cpp
    menus/MenuScreen_Shell_Settings.cpp
    menus/MenuScreen_Shell_Singleplayer.cpp
    menus/MenuScreen_Shell_Stereoscopics.cpp
    menus/MenuScreen_Shell_SystemOptions.cpp
    menus/MenuWidget.cpp
    menus/MenuWidget_Button.cpp
    menus/MenuWidget_Carousel.cpp
    menus/MenuWidget_CommandBar.cpp
    menus/MenuWidget_DynamicList.cpp
    menus/MenuWidget_Help.cpp
    menus/MenuWidget_InfoBox.cpp
    menus/MenuWidget_ItemAssignment.cpp
    menus/MenuWidget_List.cpp
    menus/MenuWidget_LobbyList.cpp
    menus/MenuWidget_MenuBar.cpp
    menus/MenuWidget_NavBar.cpp
    menus/MenuWidget_NavButton.cpp
    menus/MenuWidget_PDA_AudioFiles.cpp
    menus/MenuWidget_PDA_EmailInbox.cpp
    menus/MenuWidget_PDA_Objective.cpp
    menus/MenuWidget_PDA_UserData.cpp
    menus/MenuWidget_PDA_VideoInfo.cpp
    menus/MenuWidget_Scrollbar.cpp
    menus/MenuWidget_Shell_SaveInfo.cpp
    physics/Clip.cpp
    physics/Force.cpp
    physics/Force_Constant.cpp
    physics/Force_Drag.cpp
    physics/Force_Field.cpp
    physics/Force_Grab.cpp
    physics/Force_Spring.cpp
    physics/Physics.cpp
    physics/Physics_Actor.cpp
    physics/Physics_AF.cpp
    physics/Physics_Base.cpp
    physics/Physics_Monster.cpp
    physics/Physics_Parametric.cpp
    physics/Physics_Player.cpp
    physics/Physics_RigidBody.cpp
    physics/Physics_Static.cpp
    physics/Physics_StaticMulti.cpp
    physics/Push.cpp
    script/Script_Compiler.cpp
    script/Script_Interpreter.cpp
    script/Script_Program.cpp
    script/Script_Thread.cpp
    Actor.cpp
    AF.cpp
    AFEntity.cpp
    BrittleFracture.cpp
    Camera.cpp
    Entity.cpp
    Fx.cpp
    Game_local.cpp
    Game_network.cpp
    GameEdit.cpp
    Grabber.cpp
    IK.cpp
    Item.cpp
    Light.cpp
    Misc.cpp
    Moveable.cpp
    Mover.cpp
    MultiplayerGame.cpp
    Player.cpp
    PlayerIcon.cpp
    PlayerView.cpp
    Projectile.cpp
    Pvs.cpp
    SecurityCamera.cpp
    SmokeParticles.cpp
    Sound.cpp
    Target.cpp
    Trigger.cpp
    Weapon.cpp
    WorldSpawn.cpp)

set(GAMED3XP_HDR
    Achievements.h
    AimAssist.h
    ai/AAS.h
    ai/AAS_local.h
    ai/AI.h
    anim/Anim.h
    anim/Anim_Testmodel.h
    gamesys/Class.h
    gamesys/Event.h
    gamesys/SaveGame.h
    gamesys/SysCmds.h
    gamesys/SysCvar.h
    Leaderboards.h
    menus/MenuHandler.h
    menus/MenuScreen.h
    menus/MenuWidget.h
    physics/Clip.h
    physics/Force.h
    physics/Force_Constant.h
    physics/Force_Drag.h
    physics/Force_Field.h
    physics/Force_Grab.h
    physics/Force_Spring.h
    physics/Physics.h
    physics/Physics_Actor.h
    physics/Physics_AF.h
    physics/Physics_Base.h
    physics/Physics_Monster.h
    physics/Physics_Parametric.h
    physics/Physics_Player.h
    physics/Physics_RigidBody.h
    physics/Physics_Static.h
    physics/Physics_StaticMulti.h
    physics/Push.h
    PredictedValue.h
    PredictedValue_impl.h
    script/Script_Compiler.h
    script/Script_Interpreter.h
    script/Script_Program.h
    script/Script_Thread.h
    Actor.h
    AF.h
    AFEntity.h
    BrittleFracture.h
    Camera.h
    Entity.h
    Fx.h
    Game.h
    Game_local.h
    GameEdit.h
    Grabber.h
    IK.h
    Item.h
    Light.h
    Misc.h
    Moveable.h
    Mover.h
    MultiplayerGame.h
    Player.h
    PlayerIcon.h
    PlayerView.h
    Projectile.h
    Pvs.h
    SecurityCamera.h
    SmokeParticles.h
    Sound.h
    Target.h
    Trigger.h
    Weapon.h
    WorldSpawn.h)

# file(GLOB GAMED3XP_ROOT_SRC ${GAMED3XP_DIR}/*.cpp)
# file(GLOB GAMED3XP_ROOT_HDR ${GAMED3XP_DIR}/*.h)
# file(GLOB GAMED3XP_AI_SRC ${GAMED3XP_DIR}/ai/*.cpp)
# file(GLOB GAMED3XP_AI_HDR ${GAMED3XP_DIR}/ai/*.h)
# file(GLOB GAMED3XP_ANIM_SRC ${GAMED3XP_DIR}/anim/*.cpp)
# file(GLOB GAMED3XP_ANIM_HDR ${GAMED3XP_DIR}/anim/*.h)
# file(GLOB GAMED3XP_GAMESYS_SRC ${GAMED3XP_DIR}/gamesys/*.cpp)
# file(GLOB GAMED3XP_GAMESYS_HDR ${GAMED3XP_DIR}/gamesys/*.h)
# file(GLOB GAMED3XP_MENUS_SRC ${GAMED3XP_DIR}/menus/*.cpp)
# file(GLOB GAMED3XP_MENUS_HDR ${GAMED3XP_DIR}/menus/*.h)
# file(GLOB GAMED3XP_PHYSICS_SRC ${GAMED3XP_DIR}/physics/*.cpp)
# file(GLOB GAMED3XP_PHYSICS_HDR ${GAMED3XP_DIR}/physics/*.h)
# file(GLOB GAMED3XP_SCRIPT_SRC ${GAMED3XP_DIR}/script/*.cpp)
# file(GLOB GAMED3XP_SCRIPT_HDR ${GAMED3XP_DIR}/script/*.h)

# source_group(TREE "${GAMED3XP_DIR}/ai" FILES ${GAMED3XP_AI_SRC})

# set(GAMED3XP_SRC ${GAMED3XP_ROOT_SRC} ${GAMED3XP_AI_SRC} ${GAMED3XP_ANIM_SRC}
# ${GAMED3XP_GAMESYS_SRC} ${GAMED3XP_MENUS_SRC} ${GAMED3XP_PHYSICS_SRC}
# ${GAMED3XP_SCRIPT_SRC}) set(GAMED3XP_HDR ${GAMED3XP_ROOT_HDR}
# ${GAMED3XP_AI_HDR} ${GAMED3XP_ANIM_HDR} ${GAMED3XP_GAMESYS_HDR}
# ${GAMED3XP_MENUS_HDR} ${GAMED3XP_PHYSICS_HDR} ${GAMED3XP_SCRIPT_HDR})

target_sources(gamed3xp PRIVATE ${GAMED3XP_HDR} ${GAMED3XP_SRC})

target_compile_definitions(gamed3xp PRIVATE __DOOM__ _D3XP CTF)

target_precompile_headers(gamed3xp REUSE_FROM precompiled)
target_link_libraries(gamed3xp PRIVATE neo_preprocessor_definitions)
