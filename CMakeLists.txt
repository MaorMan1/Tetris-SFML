cmake_minimum_required(VERSION 3.10)
project(TetrisSFML)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(headers)

# Find dynamic SFML
find_package(SFML COMPONENTS Graphics Window System Audio CONFIG REQUIRED)

# Add executable and all source files
add_executable(TetrisSFML
    src/main.cpp
    src/Board.cpp
    src/Bar.cpp
    src/CubePattern.cpp
    src/Game.cpp
    src/Pattern_I.cpp
    src/MenuMain.cpp
    src/AboutPage.cpp
    src/ResourcesManager.cpp
    src/DelayTimer.cpp
    src/GamePlayPage.cpp
    src/GravityTimer.cpp
    src/Pattern_O.cpp
    src/Pattern_T.cpp
    src/Pattern_J.cpp
    src/Pattern_L.cpp
    src/Pattern_S.cpp
    src/Pattern_Z.cpp
    src/LineClearAnimation.cpp
    src/ShakeManager.cpp
    src/FireTrailAnimation.cpp
    src/UIBar.cpp
    src/DisplayWindow.cpp
    src/UIButton.cpp
    src/ButtonRetry.cpp
    src/ButtonPause.cpp
    src/ButtonBackToMenu.cpp
    src/LeaderBoardUtils.cpp
    src/LeaderBoardPage.cpp
    src/ButtonMute.cpp
    src/ScorePopup.cpp
)

if(WIN32)
    target_sources(TetrisSFML PRIVATE ${CMAKE_SOURCE_DIR}/resources/icon.rc)
endif()


# Link SFML dynamically
target_link_libraries(TetrisSFML 
    PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)

# Copy resources folder on build
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
