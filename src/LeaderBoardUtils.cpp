#include "LeaderboardUtils.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

void loadScoresFromFile(const std::string& filePath, std::vector<ScoreEntry>& scores) {
    scores.clear();
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Not opened";
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (std::getline(iss, name, ':') && iss >> score) {
            scores.push_back({ name, score });
        }
    }

    // Sort descending and keep top 5
    std::sort(scores.begin(), scores.end());
    if (scores.size() > 5)
        scores.resize(5);
}

void saveScoresToFile(const std::string& filePath, const std::vector<ScoreEntry>& scores) {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Not opened";
    }

    //debugging
    /*std::cout << "Current path: " << std::filesystem::current_path() << std::endl;*/


    for (const auto& entry : scores) {
        file << entry.name << ":" << entry.score << "\n";
    }
}
