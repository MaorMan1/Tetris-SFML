#include "MenuMain.hpp"


MenuMain::MenuMain(sf::RenderWindow& window):
    m_selected(MenuOptions::None),
    m_font(ResourcesManager::get().getFont("main")),
    m_music(&ResourcesManager::get().getMusic("menu")),
    m_menuBGSprite(ResourcesManager::get().getTexture("menu_bg_pic")),
    m_pendingClick("")
{
    m_fillColor.r = 255;
    m_fillColor.g = 215;
    m_fillColor.b = 160;

    m_outlineColor.r = 184;
    m_outlineColor.g = 134;
    m_outlineColor.b = 11;

    //scaling to window size
    sf::Vector2f scale = { static_cast<float>(window.getSize().x) / static_cast<float>(m_menuBGSprite.getTexture().getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(m_menuBGSprite.getTexture().getSize().y) };
    m_menuBGSprite.setScale(scale);

    m_music->setLooping(true);
    m_music->play();
    m_menuOptions.reserve(static_cast<int>(MenuOptions::Count));
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    sf::Text playop(m_font);
    sf::Text aboutop(m_font);
    sf::Text leadersop(m_font);
    sf::Text exitop(m_font);

    playop.setString("Play");
    aboutop.setString("About");
    leadersop.setString("Leaders board");
    exitop.setString("Exit");

    int charSize = 40;
    playop.setCharacterSize(charSize);
    aboutop.setCharacterSize(charSize);
    leadersop.setCharacterSize(charSize);
    exitop.setCharacterSize(charSize);

    // Store them in a vector
    m_menuOptions = { playop, aboutop, leadersop, exitop };

    // Calculate total height
    float totalHeight = m_menuOptions.size() * charSize + (m_menuOptions.size() - 1) * 20;
    float startY = (windowHeight - totalHeight) / 2.f;
    // Position each text centered
    for (std::size_t i = 0; i < m_menuOptions.size(); ++i) {
        auto bounds = m_menuOptions[i].getLocalBounds(); 
        float x = (windowWidth - static_cast<float>(bounds.size.x)) / 2.f;
        float y = startY + i * (charSize + 20); // 20 is vertical padding
        m_menuOptions[i].setOutlineColor(m_outlineColor);
        m_menuOptions[i].setOutlineThickness(3);
        m_menuOptions[i].setPosition({ x, y });
    }

}

MenuMain::~MenuMain()
{
    stopMenuBackGroundMusic();
}

void MenuMain::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos(static_cast<float>(mousePixel.x), static_cast<float>(mousePixel.y));

    // Handle Hover
    if (event.is<sf::Event::MouseMoved>()) {
        for (auto& option : m_menuOptions) {
            if (option.getGlobalBounds().contains(mousePos)) {
                option.setFillColor(sf::Color(255, 165, 0));     // Orange
                option.setOutlineColor(sf::Color(139, 69, 19));  // Saddle Brown
            }
            else {
                option.setFillColor(m_fillColor);
                option.setOutlineColor(m_outlineColor);
            }
        }
    }

    // Handle Press
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            for (auto& option : m_menuOptions) {
                if (option.getGlobalBounds().contains(mousePos)) {
                    ResourcesManager::get().getSound("mouse_click").play();
                    option.setFillColor(sf::Color(205, 92, 92)); // Click color
                    m_pendingClick = option.getString();         // Save label for release
                    break;
                }
            }
        }
    }

    // Handle Release
    if (event.is<sf::Event::MouseButtonReleased>()) {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            for (auto& option : m_menuOptions) {
                if (option.getGlobalBounds().contains(mousePos) &&
                    option.getString() == m_pendingClick) {

                    const std::string& label = option.getString();
                    if (label == "Play")
                        m_selected = MenuOptions::Play;
                    else if (label == "About")
                        m_selected = MenuOptions::About;
                    else if (label == "Leaders board")
                        m_selected = MenuOptions::LeadersBoard;
                    else if (label == "Exit")
                        m_selected = MenuOptions::Exit;
                    break;
                }
            }
            m_pendingClick.clear(); // Reset after release
        }
    }
}


void MenuMain::draw(sf::RenderWindow& window)
{
    window.draw(m_menuBGSprite);

    for (const auto& option : m_menuOptions)
        window.draw(option);
}

MenuOptions MenuMain::getSelection() const
{
    return m_selected;
}

void MenuMain::resetSelection() 
{
    m_selected = MenuOptions::None;

    //reset all colors
    for (auto& option : m_menuOptions) {
        option.setFillColor(m_fillColor);
        option.setOutlineColor(m_outlineColor);
    }
}

void MenuMain::stopMenuBackGroundMusic()
{
    if (m_music->getStatus() == sf::SoundSource::Status::Playing)
        m_music->stop();
}

void MenuMain::playMenuBackGroundMusic()
{
    if (m_music->getStatus() == sf::SoundSource::Status::Stopped ||
        m_music->getStatus() == sf::SoundSource::Status::Paused)
        m_music->play();
}
