#ifndef TETRIS_FIRETRAILANIMATION_HPP
#define TETRIS_FIRETRAILANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "BaseAnimation.hpp"
#include "ResourcesManager.hpp"

class FireTrailAnimation : public BaseAnimation {
public:
    FireTrailAnimation();

    void start(const sf::Vector2f& position);  // Called when Down key pressed
    void stop();                               // Called when released or locked

    void update(sf::Time dt) override;
    void draw(sf::RenderWindow& window, float blockSize, sf::Vector2f boardOffset) override;
    bool isFinished() const override;

private:
    sf::Texture* m_texture = nullptr;
    std::vector<sf::IntRect> m_frames;
    int m_currentFrame = 0;
    bool m_loopMode = false;
    bool m_active = false;
    sf::Time m_elapsed;
    sf::Time m_frameTime;
    sf::Sprite m_sprite;

    sf::Vector2f m_worldPosition;

    void updateSpriteFrame();  // Updates current frame & origin

};

#endif
