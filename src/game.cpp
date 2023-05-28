#include <fstream>
#include <game/game.h>
#include <istream>

#include <iostream>

namespace mtt {
Game::Game(std::string configFile)
{
    init(configFile);
}

inline void checkType(std::istream& input, const std::string& expectedType)
{
    std::string type;
    input >> type;
    if (type != expectedType) {
        throw mtt::ConfigException {
            .Message = "Expected " + expectedType + " config section got: " + type,
        };
    }
}

mtt::WindowConfig getWindowConfig(std::istream& input)
{
    checkType(input, "Window");
    WindowConfig config;
    input >> config.Width >> config.Height >> config.FrameRateLimit >> config.FullScreen;
    return config;
}

FontConfig getFontConfig(std::istream& input)
{
    checkType(input, "Font");
    FontConfig fc;
    input >> fc.File >> fc.Size;
    input >> fc.FontColor.R >> fc.FontColor.G >> fc.FontColor.B;
    return fc;
}

PlayerConfig getPlayerConfig(std::istream& input)
{
    checkType(input, "Player");
    PlayerConfig pc;
    input >> pc.ShapeRadius >> pc.CollisionRadius >> pc.Speed;
    input >> pc.FillColor.R >> pc.FillColor.G >> pc.FillColor.B;
    input >> pc.OutlineColor.R >> pc.OutlineColor.G >> pc.OutlineColor.B;
    input >> pc.OutlineThickness >> pc.Vertices;
    return pc;
}

EnemyConfig getEnemyConfig(std::istream& input)
{
    checkType(input, "Enemy");
    EnemyConfig ec;
    input >> ec.ShapeRadius >> ec.CollisionRadius >> ec.MinSpeed >> ec.MaxSpeed;
    input >> ec.OutlineColor.R >> ec.OutlineColor.G >> ec.OutlineColor.B;
    input >> ec.OutlineThickness >> ec.MinVertices >> ec.MaxVertices;
    input >> ec.SmallLifespan >> ec.SpawnCooldown;
    return ec;
}

BulletConfig getBulletConfig(std::istream& input)
{
    checkType(input, "Bullet");
    BulletConfig bc;
    input >> bc.ShapeRadius >> bc.CollisionRadius >> bc.Speed;
    input >> bc.FillColor.R >> bc.FillColor.G >> bc.FillColor.B;
    input >> bc.OutlineColor.R >> bc.OutlineColor.G >> bc.OutlineColor.B;
    input >> bc.OutlineThickness >> bc.Lifespan;
    return bc;
}

void Game::init(std::string configFile)
{
    std::fstream file(configFile);
    WindowConfig windowConfig = getWindowConfig(file);
    FontConfig fontConfig = getFontConfig(file);
    playerConfig = getPlayerConfig(file);
    enemyConfing = getEnemyConfig(file);
    bulletConfig = getBulletConfig(file);

    // init window
    window.create(windowConfig);
    font = fromConfigs(fontConfig);
    score.setUp(font, fontConfig.Size, fontConfig.FontColor);
    score.updateText();
}

void Game::sRender()
{
    window.clear();

    for (auto e : entities.getEntities())
    {
        if (e->cShape != nullptr)
        {
            window.draw(e->cShape->circle);
        }
    }

    window.draw(score.Text);
    window.display();
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
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Closing window\n";
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::F:
                window.toggleFullScreen();
                break;
            default:
                break;
            }
        }
    }
}

void Game::spawnPlayer()
{
    player = entities.addEntity("player");
    player->cInput = std::make_shared<CInput>();
    player->cShape = std::make_shared<CShape>(
        playerConfig.ShapeRadius,
        playerConfig.Vertices,
        sf::Color(
            playerConfig.FillColor.R,
            playerConfig.FillColor.B,
            playerConfig.FillColor.G
        ),
        sf::Color(
            playerConfig.OutlineColor.R,
            playerConfig.OutlineColor.B,
            playerConfig.OutlineColor.G
        ),
        playerConfig.OutlineThickness
    );
    //player->cCollision = std::make_shared<CCollision>();
    //player->cTransform = std::make_shared<CTransform>();

    player->cShape->circle.setOrigin(0, 0);
    Vec2 windowSize = window.getSize();
    player->cShape->circle.setPosition(windowSize.x / 2, windowSize.y/2);
}

int Game::run()
{
    spawnPlayer();
    while (window.isOpen()) {
        entities.update();

        if (!paused)
        {
            currentFrame++;
        }

        sUserInput();
        sRender();
    }
    return 0;
}

sf::Font fromConfigs(const FontConfig & configs)
{
    sf::Font font;
    if (!font.loadFromFile(configs.File))
    {
        throw FontNotFound {
            .Message = "Font " + configs.File + " not found",
        };
    }
    return font;
}
}
