cmake_minimum_required(VERSION 3.21)
project(PolyominoSFML LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(src/GUI)
include_directories(src/SFX)
include_directories(src/states)
include_directories(src/GUI)
include_directories(src/utils)

add_executable(PolyominoSFML 
    src/GUI/button.h 
    src/GUI/component.h 
    src/GUI/container.h 
    src/GUI/label.h 
    src/SFX/music_player.h 
    src/SFX/sound_player.h 
    src/application.h 
    src/const/state_identifiers.h 
    src/player.h 
    src/polyomino.h 
    src/states/game_over_state.h 
    src/states/game_state.h 
    src/states/menu_state.h 
    src/states/pause_state.h 
    src/states/state.h 
    src/states/state_stack.h 
    src/states/title_state.h 
    src/utils/resource_holder.h 
    src/utils/resource_identifiers.h 
    src/world.h
    src/GUI/button.cpp 
    src/GUI/component.cpp 
    src/GUI/container.cpp 
    src/GUI/label.cpp 
    src/SFX/music_player.cpp 
    src/SFX/sound_player.cpp 
    src/application.cpp 
    src/main.cpp 
    src/player.cpp 
    src/polyomino.cpp 
    src/states/game_over_state.cpp 
    src/states/game_state.cpp 
    src/states/menu_state.cpp 
    src/states/pause_state.cpp 
    src/states/state.cpp 
    src/states/state_stack.cpp 
    src/states/title_state.cpp 
    src/world.cpp
)
target_link_libraries(PolyominoSFML PRIVATE sfml-window sfml-graphics sfml-system sfml-audio)
target_compile_features(PolyominoSFML PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET PolyominoSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PolyominoSFML> $<TARGET_FILE_DIR:Polyomino> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS PolyominoSFML)

