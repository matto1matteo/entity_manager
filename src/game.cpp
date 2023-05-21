#include <fstream>
#include <game/game.h>
#include <istream>

#include <iostream>

Game::Game(std::string configFile)
    : m_window(sf::VideoMode(600, 400), "EntityManager")
{
    init(configFile);
}

void checkType(std::istream& input, const std::string& expectedType)
{
    std::string type;
    input >> type;
    if (type != expectedType) {
        throw ConfigException {
            .Message = "Expected " + expectedType + " config section got: " + type,
        };
    }
}

WindowConfig getWindowConfig(std::istream& input)
{
    WindowConfig config;
    checkType(input, "Window");
    input >> config.Width >> config.Height >> config.FrameRateLimit >> config.FullScreen;
    return config;
}

FontConfig getFontConfig(std::istream& input)
{
    FontConfig fc;
    checkType(input, "Font");
    input >> fc.File >> fc.Size >> fc.R >> fc.G >> fc.B;
    return fc;
}

PlayerConfig getPlayerConfig(std::istream& input)
{
    PlayerConfig pc;
    checkType(input, "Player");
    input >> pc.ShapeRadius >> pc.CollisionRadius >> pc.Speed;
    input >> pc.FillColor.R >> pc.FillColor.G >> pc.FillColor.B;
    input >> pc.OutlineColor.R >> pc.OutlineColor.G >> pc.OutlineColor.B;
    input >> pc.OutlineThickness >> pc.Vertices;
    return pc;
}

EnemyConfig getEnemyConfig(std::istream& input)
{
    EnemyConfig ec;
    checkType(input, "Enemy");
    input >> ec.ShapeRadius >> ec.CollisionRadius >> ec.MinSpeed >> ec.MaxSpeed;
    input >> ec.OutlineColor.R >> ec.OutlineColor.G >> ec.OutlineColor.B;
    input >> ec.OutlineThickness >> ec.MinVertices >> ec.MaxVertices;
    input >> ec.SmallLifespan >> ec.SpawnCooldown;
    return ec;
}

BulletConfig getBulletConfig(std::istream& input)
{
    BulletConfig bc;
    std::string type;
    checkType(input, "Bullet");
    input >> bc.ShapeRadius >> bc.CollisionRadius >> bc.Speed;
    input >> bc.FillColor.R >> bc.FillColor.G >> bc.FillColor.B;
    input >> bc.OutlineColor.R >> bc.OutlineColor.G >> bc.OutlineColor.B;
    input >> bc.OutlineThickness >> bc.Lifespan;
    return bc;
}

void Game::init(std::string configFile)
{
    std::fstream file(configFile);
    WindowConfig window = getWindowConfig(file);
    FontConfig font = getFontConfig(file);
    PlayerConfig player = getPlayerConfig(file);
    EnemyConfig enemy = getEnemyConfig(file);
    BulletConfig bullet = getBulletConfig(file);

    window.FullScreen = true;
    if (window.FullScreen)
    {
        m_window.create(
            sf::VideoMode::getFullscreenModes()[0],
            "EntityManager",
            sf::Style::Fullscreen
        );
    }
    else
    {
        m_window.create(
            sf::VideoMode(window.Width, window.Height),
            "EntityManager"
        );
    }
    m_window.setFramerateLimit(window.FrameRateLimit);
}

void Game::sRender()
{
    m_window.clear();
    m_window.display();
}

bool isFullScreen(const sf::RenderWindow & window)
{
    auto windowSize = window.getSize();
    auto screenSize = sf::VideoMode::getDesktopMode();

    return (windowSize.x == screenSize.width)
        && (windowSize.y == screenSize.height);
}

void Game::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Closing window\n";
            m_window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                std::cout << "Closing window\n";
                m_window.close();
                break;
            case sf::Keyboard::F:
                std::cout << "Toggling full screen\n";
                std::cout << "Is full screen: " << isFullScreen(m_window) << "\n";
                break;
            default:
                break;
            }
        }
    }
}

int Game::run()
{
    while (m_window.isOpen()) {
        sUserInput();
        sRender();
    }
    return 0;
}
