#ifndef TETRIS_SCOREENTRY_HPP
#define TETRIS_SCOREENTRY_HPP

#include <string>

struct ScoreEntry {
    std::string name;
    int score;

    bool operator<(const ScoreEntry& other) const {
        // Higher scores come first
        return score > other.score;
    }
};

#endif
