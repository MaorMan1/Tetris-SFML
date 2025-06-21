#ifndef TETRIS_GLOBALS_HPP
#define TETRIS_GLOBALS_HPP

#include <iostream>
#include <string>

/**
 * @file Globals.hpp
 * @brief Shared global constants and enums used across the Tetris game.
 *
 * This header defines board dimensions, UI sizing, enums for game logic,
 * and configuration constants like file paths and button options.
 */

 // ====== Board Configuration ======
const int WIDTH = 10;   ///< Number of columns in the Tetris board
const int HEIGHT = 20;  ///< Number of rows in the Tetris board

// ====== UI Bar Configuration ======
const int UI_WIDTH = 150; ///< Width (in pixels) of the right-side UI bar

// ====== Score File Path ======
// NOTE: Adjust this path based on your actual working directory if needed
const std::string SCORESFILE = "../../../resources/scores.txt";

// ====== Game Pattern Types ======
enum class Patterns {
    I, O, T, J, L, S, Z, Count
};

// ====== Main Menu Options ======
enum class MenuOptions {
    Play,
    About,
    LeadersBoard,
    Exit,
    Count,
    None
};

// Enable comparing integers with MenuOptions (used in loops/selections)
inline bool operator<(int lhs, MenuOptions rhs) {
    return lhs < static_cast<int>(rhs);
}

// ====== Pattern Rotation State ======
enum class PatternPosition {
    _0deg,
    _90deg,
    _180deg,
    _270deg
};

// ====== Display Widgets in UI Bar ======
enum class DisplaysOptions {
    Score,
    NextPattern
};

// ====== Button Types for UI ======
enum class Button {
    Pause,
    Play,
    Retry,
    Home,
    Mute,
    Unmute,
    None
};

// ====== Button Hover or Click Status ======
enum class ButtonStatus {
    Normal,
    Clicked,
    Hovered
};

// ====== Meme Audio Options ======
enum class FunnyMemes {
    Nice,
    Omg,
    Wow,
    YeahBoy,
    Breakfast,
    Amount ///< Used to indicate enum count (rand() % Amount)
};

#endif
