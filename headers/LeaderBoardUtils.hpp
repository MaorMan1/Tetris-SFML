#ifndef TETRIS_LEADERBOARDUTILS_HPP
#define TETRIS_LEADERBOARDUTILS_HPP

#include "ScoreEntry.hpp"
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Loads score entries from a file into the provided vector.
 * @param filePath The path to the scores file.
 * @param scores The vector to populate with loaded scores.
 */
void loadScoresFromFile(const std::string& filePath, std::vector<ScoreEntry>& scores);

/**
 * @brief Saves the given vector of scores to a file.
 * @param filePath The path to save the scores.
 * @param scores The vector of scores to write.
 */
void saveScoresToFile(const std::string& filePath, const std::vector<ScoreEntry>& scores);

#endif
