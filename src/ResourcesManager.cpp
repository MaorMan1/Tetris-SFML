#include "ResourcesManager.hpp"
#include <stdexcept>

ResourcesManager& ResourcesManager::get()
{
	static ResourcesManager instance;
	return instance;
}

void ResourcesManager::loadFont(const std::string& name, const std::string& path)
{
    sf::Font font;
    if (!font.openFromFile(path)) {
        throw std::runtime_error("Cannot load font: " + path); // We are inside the try in Game::loadResources function
    }
    m_fonts[name] = std::move(font);
}

sf::Font& ResourcesManager::getFont(const std::string& name)
{
    return m_fonts.at(name); // Catches mistakes if not exists
}

void ResourcesManager::loadMusic(const std::string& name, const std::string& path)
{
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(path)) {
        throw std::runtime_error("Cannot load music: " + path); // We are inside the try in Game::loadResources function
    }
    m_music[name] = std::move(music);
}

sf::Music& ResourcesManager::getMusic(const std::string& name)
{
    auto it = m_music.find(name);
    if (it == m_music.end())
        throw std::runtime_error("Music not found: " + name);
    return *it->second;
}

void ResourcesManager::loadSound(const std::string& name, const std::string& path)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path)) {
        throw std::runtime_error("Cannot load sound file: " + path);
    }

    // Insert buffer into hash map
    m_soundBuffers[name] = std::move(buffer);

    // Create the sf::Sound and set its buffer
    auto sound = std::make_unique<sf::Sound>(m_soundBuffers[name]);
    //sound->setBuffer(m_soundBuffers[name]);
    // Store the sf::Sound
    m_sounds[name] = std::move(sound);
}

sf::Sound& ResourcesManager::getSound(const std::string& name)
{
    auto it = m_sounds.find(name);
    if (it == m_sounds.end()) {
        throw std::runtime_error("Sound not found: " + name);
    }
    return *it->second;
    // Later...
    //ResourcesManager::get().getSound("click").play();
}

void ResourcesManager::loadTexture(const std::string& name, const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Cannot load texture: " + path); // We are inside the try in Game::loadResources function
    }
    m_textures[name] = std::move(texture);
}

sf::Texture& ResourcesManager::getTexture(const std::string& name)
{
    return m_textures.at(name);
}
