#ifndef TETRIS_GLOBALS_HPP
#define TETRIS_GLOBALS_HPP
#include <iostream>



//Board matrix size:
const int WIDTH = 10;
const int HEIGHT = 20;

//UI Bar
const int UI_WIDTH = 150;

// Originally its working on ...//out//build//debug so go back 3 folders to the real resources folder:
const std::string SCORESFILE = "../../../resources/scores.txt"; 

//enum class GameState {
//    Menu,
//    Playing,
//    GameOver,
//    About
//};

enum class Patterns {
    I,
    O,
    T,
    J,
    L,
    S,
    Z,
    Count
};

enum class MenuOptions {
    Play,
    About,
    LeadersBoard,
    Exit,
    Count,
    None
};

inline bool operator<(int lhs, MenuOptions rhs) {
    return lhs < static_cast<int>(rhs);
}
//inline bool operator!=(MenuOptions lhs, GameState rhs) {
//    return static_cast<int>(lhs) != static_cast<int>(rhs);
//}

//?
enum class PatternPosition {
    _0deg,
    _90deg,
    _180deg,
    _270deg
};


enum class DisplaysOptions
{
    Score,
    NextPattern
};
enum class Button {
    Pause,
    Play,
    Retry,
    Home,
    None
};
enum class ButtonStatus {
    Normal,
    Clicked,
    Hovered
};
#endif 
