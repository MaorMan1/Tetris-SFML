#include "AboutPage.hpp"

AboutPage::AboutPage(sf::RenderWindow& window):
    m_hoverBack(false),
    m_font(ResourcesManager::get().getFont("main")),
    m_aboutBGSprite(ResourcesManager::get().getTexture("about_bg_pic"))
{
    //m_backToMenu = false;
    //scaling bg to window size
    sf::Vector2f scale = { static_cast<float>(window.getSize().x) / static_cast<float>(m_aboutBGSprite.getTexture().getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(m_aboutBGSprite.getTexture().getSize().y) };
    m_aboutBGSprite.setScale(scale);

    sf::Text title(m_font);
    sf::Text description(m_font);
    sf::Text backButton(m_font);


    title.setString("About This Game:");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Cyan);
    auto bounds = title.getLocalBounds();
    float x = (window.getSize().x - bounds.size.x) / 2.f;
    sf::Vector2f pos = { x, 100 };
    title.setPosition(pos); // centered-ish

    //description setup
    description.setString(
        "This is a Tetris remake project.\n"
        "Made by Maor Man with C++ and SFML.\n"
        "For learning and fun!\n\n"
        "Keys:\n"
        "Left key: Moving left.\n"
        "Right key: Moving right.\n"
        "Down key: Moving down faster.\n"
        "Up key: For rotating piece.\n\n"
        "The rules you already know :)\n"
        "Enjoy!"
    );
    description.setCharacterSize(24);
    description.setFillColor(sf::Color::White);
    pos = { x, 200 };
    description.setPosition(pos);

    //back button setup
    backButton.setString("<< Back to Menu");
    backButton.setCharacterSize(30);
    backButton.setFillColor(sf::Color::White);
    pos = { 15,15 };
    backButton.setPosition(pos);
    sf::Vector2f v = { 1.05f, 1.05f };
    backButton.setScale(v);

    m_AboutPageList = { title, description, backButton };
}

void AboutPage::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    auto& backButton = m_AboutPageList.back(); //The last is Back button

    if (event.is<sf::Event::MouseMoved>()) {
        sf::Vector2i mouseP = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos(static_cast<float>(mouseP.x), static_cast<float>(mouseP.y));
        //std::cout << mousePos.x << " " << mousePos.y << std::endl;

        if (backButton.getGlobalBounds().contains(mousePos)) {
            m_hoverBack = true; 
            backButton.setFillColor(sf::Color::Yellow);
        }
        else {
            m_hoverBack = false;
            backButton.setFillColor(sf::Color::White);
        }
        
    }
    if (event.is<sf::Event::MouseButtonPressed>()) {
        ResourcesManager::get().getSound("mouse_click").play();
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent->button == sf::Mouse::Button::Left && m_hoverBack)
            m_backToMenu = true;
        /*else
            m_backToMenu = false;*/
    }
}

void AboutPage::draw(sf::RenderWindow& window)
{
    window.draw(m_aboutBGSprite);
    for (const auto& text : m_AboutPageList)
        window.draw(text);
}

void AboutPage::resetAboutPage()
{
    m_backToMenu = false;
    m_hoverBack = false;
    m_AboutPageList.back().setFillColor(sf::Color::White);
}
