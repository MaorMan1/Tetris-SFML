#ifndef TETRIS_RESOURCESMANAGER_HPP
#define TETRIS_RESOURCESMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include "DelayTimer.hpp"
#include "Globals.hpp"

/**
 * @class ResourcesManager
 * @brief Singleton that manages loading and accessing textures, fonts, sounds, and music.
 */
class ResourcesManager {
public:
    /**
     * @brief Returns the singleton instance of the ResourcesManager.
     */
    static ResourcesManager& get();

    // Font Management
    void loadFont(const std::string& name, const std::string& path);
    sf::Font& getFont(const std::string& name);

    // Music Management
    void loadMusic(const std::string& name, const std::string& path);
    sf::Music& getMusic(const std::string& name);

    // Sound Effects Management
    void loadSound(const std::string& name, const std::string& path);
    sf::Sound& getSound(const std::string& name);

    // Texture Management
    void loadTexture(const std::string& name, const std::string& path);
    sf::Texture& getTexture(const std::string& name);

private:
    // Singleton Pattern
    ResourcesManager() = default;
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    // Resource Containers
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers; // Holds the data - effects:
    std::unordered_map<std::string, std::unique_ptr<sf::Sound>> m_sounds;  // To use them
    std::unordered_map<std::string, sf::Texture> m_textures;
};

#endif 
