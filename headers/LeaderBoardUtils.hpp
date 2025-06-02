#ifndef TETRIS_LEADERBOARDUTILS_HPP
#define TETRIS_LEADERBOARDUTILS_HPP

#include "ScoreEntry.hpp"
#include <vector>
#include <string>
#include <iostream>

void loadScoresFromFile(const std::string& filePath, std::vector<ScoreEntry>& scores);
void saveScoresToFile(const std::string& filePath, const std::vector<ScoreEntry>& scores);

#endif
