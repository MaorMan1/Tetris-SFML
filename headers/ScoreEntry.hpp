#ifndef TETRIS_SCOREENTRY_HPP
#define TETRIS_SCOREENTRY_HPP

#include <string>

/**
 * @struct ScoreEntry
 * @brief Holds the player's name and score for the leaderboard.
 */
struct ScoreEntry {
    std::string name;
    int score;

    /**
     * @brief Comparator for sorting in descending score order.
     *        This ensures higher scores come before lower ones.
     */
    bool operator<(const ScoreEntry& other) const {
        // Higher scores come first
        return score > other.score;
    }

    // Optional for later: Add if needed
    // bool operator==(const ScoreEntry& other) const {
    //     return name == other.name && score == other.score;
    // }

    // friend std::ostream& operator<<(std::ostream& os, const ScoreEntry& entry) {
    //     return os << entry.name << ": " << entry.score;
    // }
};

#endif
