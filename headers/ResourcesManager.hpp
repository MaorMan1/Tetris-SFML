#ifndef TETRIS_RESOURCESMANAGER_HPP
#define TETRIS_RESOURCESMANAGER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include "DelayTimer.hpp"

class ResourcesManager {
public:
    static ResourcesManager& get();  // Singleton access

    // Fonts
    void loadFont(const std::string& name, const std::string& path);
    sf::Font& getFont(const std::string& name);

    // Long music
    void loadMusic(const std::string& name, const std::string& path);
    sf::Music& getMusic(const std::string& name);

    // Sound Effects
    void loadSound(const std::string& name, const std::string& path);
    sf::Sound& getSound(const std::string& name); // - TODO

    // Textures
    void loadTexture(const std::string& name, const std::string& path);
    sf::Texture& getTexture(const std::string& name);

private:
    // Private constructor = Singleton
    ResourcesManager() = default;

    // Prevent copying
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    // Storage
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers; // Holds the data - effects:
    std::unordered_map<std::string, std::unique_ptr<sf::Sound>> m_sounds;  // To use them
    std::unordered_map<std::string, sf::Texture> m_textures;
};

#endif 
