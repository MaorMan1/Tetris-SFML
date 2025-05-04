#ifndef TETRIS_LINECLEARANIMATION_HPP
#define TETRIS_LINECLEARANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>
#include "ResourcesManager.hpp"  
#include "Globals.hpp"
#include "BaseAnimation.hpp"

// Represents the animation state of a single block during line clearing
struct ExplosionBlock {
    int frame = 0;    // Current animation frame index
    bool active = false; // Whether this block has started animating
};

// Allows std::pair<int,int> to be used as a key in unordered_map
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Simple combination of two hashes
    }
};

class LineClearAnimation : public BaseAnimation{
public:
    LineClearAnimation();

    // Starts an explosion animation for the given cleared rows
    void start(const std::set<int>& rowsToClear);

    // Updates animation timing and frames
    void update(sf::Time dt) override;

    // Draws the explosion animation
    void draw(sf::RenderWindow& window, float blockSize, sf::Vector2f boardOffset) override;

    // Checks if the animation is completely finished
    bool isFinished() const override;

private:
    std::unordered_map<std::pair<int, int>, ExplosionBlock, pair_hash> m_blocks; // Tracks all exploding cells
    sf::Time m_frameDuration;  // How long between explosion activations
    sf::Time m_elapsed;        // Elapsed time since last update
    int m_currentFrame;        // (legacy) Not used directly now
    int m_activateColumn = 0;  // Which column is currently being activated
    sf::Texture* m_explosionTexture = nullptr; // Explosion sprite sheet
    std::vector<sf::IntRect> m_frames;          // List of explosion frames
    bool m_beforeExplosionPlayed;
};
#endif