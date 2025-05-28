cmake_minimum_required(VERSION 3.10)
project(TetrisSFML)

set(CMAKE_CXX_STANDARD 17)

# Use vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "C:/Users/maorm/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)

# Find SFML 3 with audio support
find_package(SFML 3 COMPONENTS Graphics Window System Audio CONFIG REQUIRED)

# Include headers directory
include_directories(headers)

# Add the executable and source files
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
 "src/DelayTimer.cpp" "src/GamePlayPage.cpp" "src/GravityTimer.cpp" "src/Pattern_O.cpp" "src/Pattern_T.cpp" "src/Pattern_J.cpp" "src/Pattern_L.cpp" "src/Pattern_S.cpp" "src/Pattern_Z.cpp" "src/LineClearAnimation.cpp" "src/ShakeManager.cpp" "src/FireTrailAnimation.cpp" "src/UIBar.cpp" "src/DisplayWindow.cpp" "src/UIButton.cpp" "src/ButtonRetry.cpp" "src/ButtonPause.cpp" "src/ButtonBackToMenu.cpp")

# Link SFML modules (modern usage)
target_link_libraries(TetrisSFML 
    PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)

# Copy the resources folder into the build folder
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
