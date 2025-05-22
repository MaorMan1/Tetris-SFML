#ifndef TETRIS_DISPLAYWINDOW_HPP
#define TETRIS_DISPLAYWINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <type_traits>
#include "CubePattern.hpp"
#include "Globals.hpp"

// Forward declaration
class CubePattern;

class DisplayWindow {
public:
    DisplayWindow(sf::Vector2f position, sf::Vector2f size, const std::string& title = "", DisplaysOptions option = DisplaysOptions::Score);

    void setValue(const std::string& value);
    void setTitle(const std::string& title);
    void draw(sf::RenderWindow& window, const int alpha = 255, const CubePattern* piece = nullptr, const float blockSize = 0.f) const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::Vector2i getDispPivot() const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Vector2i m_dispPivot;

    std::string m_title;
    std::string m_value;
    DisplaysOptions m_option;

    sf::RectangleShape m_background;
    sf::Text m_titleText;
    sf::Text m_valueText;

    // Utility function for drawing with temporary alpha
    template <class T>
    T withAlpha(const T& original, int alpha) const;
};


template<class T>
inline T DisplayWindow::withAlpha(const T& original, int alpha) const
{
    T copy = original;  // Make a copy so we don't affect the original
    sf::Color color;

    // Case 1: For sf::Text or sf::Sprite which use getColor()/setColor()
    if constexpr (std::is_same_v<T, sf::Text> || std::is_same_v<T, sf::Sprite> || std::is_base_of_v<sf::Shape, T>) {
        color = copy.getFillColor();
        color.a = alpha; // Clamp to 0-255
        copy.setFillColor(color);
    }
    // Case 2: For any other type that has setFillColor(), just in case
    else if constexpr (requires { copy.setFillColor(sf::Color()); }) {
        color = copy.getFillColor();
        color.a = alpha;
        copy.setFillColor(color);
    }

    return copy;
}

#endif

