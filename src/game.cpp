#include <fstream>
#include <game/game.h>
#include <istream>
#include <math.h>
#include <rand/random.hpp>
#include <trig/trig.hpp>

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

    for (auto e : entities.getEntities()) {
        if (e->cShape != nullptr && e->cTransform != nullptr) {
            if (e->cLifespan != nullptr)
            {
                sf::Color fillColor = e->cShape->circle.getFillColor();
                
                fillColor.a = (((float)e->cLifespan->remaning / (float)e->cLifespan->total) * 255);
                e->cShape->circle.setFillColor(fillColor);

                sf::Color outlineColor = e->cShape->circle.getOutlineColor();
                outlineColor.a = (((float)e->cLifespan->remaning / (float)e->cLifespan->total) * 255);
                e->cShape->circle.setOutlineColor(outlineColor);
            }
            window.draw(e->cShape->circle);
        }
    }

    score.updateText();
    window.draw(score.Text);

    window.display();
}

void Game::sMovement()
{
    for (auto e : entities.getEntities()) {
        if (e->cShape == nullptr
            && e->cTransform == nullptr
            && e->cCollision == nullptr) {
            continue;
        }

        // bounce big-enemy
        if (e->tag() == "big-enemy") {
            // check bounce x axis
            if (window.overflowX(*e) || window.underflowX(*e)) {
                e->cTransform->velocity = Vec2(
                    -(e->cTransform->velocity.x),
                    e->cTransform->velocity.y);
            }

            // check bounce y axis
            if (window.overflowY(*e) || window.underflowY(*e)) {
                e->cTransform->velocity = Vec2(
                    e->cTransform->velocity.x,
                    -(e->cTransform->velocity.y));
            }
        }

        // userinput movement movement
        if (e->cInput != nullptr) {
            // no user input given
            if (!(e->cInput->up
                    || e->cInput->down
                    || e->cInput->left
                    || e->cInput->right)) {
                continue;
            }

            if (e->cInput->up) {
                e->cTransform->position += Vec2(0, -e->cTransform->velocity.y);
            }
            if (window.underflowY(*e)) {
                e->cTransform->position = Vec2(
                    e->cTransform->position.x,
                    e->cShape->circle.getRadius());
            }

            if (e->cInput->down) {
                e->cTransform->position += Vec2(0, e->cTransform->velocity.y);
            }
            if (window.overflowY(*e)) {
                e->cTransform->position = Vec2(
                    e->cTransform->position.x,
                    window.getSize().y - e->cShape->circle.getRadius());
            }

            if (e->cInput->left) {
                e->cTransform->position += Vec2(-e->cTransform->velocity.x, 0);
            }
            if (window.underflowX(*e)) {
                e->cTransform->position = Vec2(
                    e->cShape->circle.getRadius(),
                    e->cTransform->position.y);
            }

            if (e->cInput->right) {
                e->cTransform->position += Vec2(e->cTransform->velocity.x, 0);
            }
            if (window.overflowX(*e)) {
                e->cTransform->position = Vec2(
                    window.getSize().x - e->cShape->circle.getRadius(),
                    e->cTransform->position.y);
            }

            e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);
        }
        // auto movement
        else {
            e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            e->cTransform->position += e->cTransform->velocity;
        }
    }
}

void Game::setPaused(bool paused)
{
    this->paused = paused;
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& pos)
{
    if (paused) {
        return;
    }
    // prepare velocity and bullet position
    Vec2 entityOrigin = entity->cTransform != nullptr
        ? entity->cTransform->position
        : Vec2(0, 0);
    float dist = entityOrigin.dist(pos);
    float teta = (pos - entityOrigin).getAngle();
    Vec2 bulletVelocity = Vec2::FromSpeedAndAngle(dist, teta).normalized() * bulletConfig.Speed;

    Vec2 bulletCenter = (bulletVelocity.normalized() * playerConfig.ShapeRadius) + entityOrigin;

    // set up bullet entity
    auto bullet = entities.addEntity("bullet");
    bullet->cTransform = std::make_shared<CTransform>(
        bulletCenter,
        bulletVelocity,
        teta);
    bullet->cShape = std::make_shared<CShape>(
        bulletConfig.ShapeRadius,
        30,
        sf::Color(
            bulletConfig.FillColor.R,
            bulletConfig.FillColor.G,
            bulletConfig.FillColor.B),
        sf::Color(
            bulletConfig.OutlineColor.R,
            bulletConfig.OutlineColor.G,
            bulletConfig.OutlineColor.B),
        bulletConfig.OutlineThickness);
    bullet->cLifespan = std::make_shared<CLifespan>(bulletConfig.Lifespan);
    bullet->cCollision = std::make_shared<CCollision>(bulletConfig.CollisionRadius);
}

void Game::sUserInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::F:
                window.toggleFullScreen();
                break;
            case sf::Keyboard::P:
                setPaused(!paused);
                break;
            case sf::Keyboard::W:
                player->cInput->up = true;
                break;
            case sf::Keyboard::A:
                player->cInput->left = true;
                break;
            case sf::Keyboard::S:
                player->cInput->down = true;
                break;
            case sf::Keyboard::D:
                player->cInput->right = true;
                break;
            default:
                break;
            }
        } else if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
            case sf::Keyboard::W:
                player->cInput->up = false;
                break;
            case sf::Keyboard::A:
                player->cInput->left = false;
                break;
            case sf::Keyboard::S:
                player->cInput->down = false;
                break;
            case sf::Keyboard::D:
                player->cInput->right = false;
                break;
            default:
                break;
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            // spawn bullet
            if (event.mouseButton.button == sf::Mouse::Left) {
                Vec2 pos = Vec2(
                    event.mouseButton.x,
                    event.mouseButton.y);
                spawnBullet(player, pos);
            }
            // spawn special wepon
            if (event.mouseButton.button == sf::Mouse::Right) { }
        }
    }
}

void Game::sLifespan()
{
    for (auto e : entities.getEntities()) {
        if (e->cLifespan == nullptr) {
            continue;
        }

        e->cLifespan->remaning -= 1;

        if (e->cLifespan->remaning == 0) {
            e->destroy();
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
            playerConfig.FillColor.G),
        sf::Color(
            playerConfig.OutlineColor.R,
            playerConfig.OutlineColor.B,
            playerConfig.OutlineColor.G),
        playerConfig.OutlineThickness);
    player->cCollision = std::make_shared<CCollision>(playerConfig.CollisionRadius);
    Vec2 windowSize = window.getSize();
    player->cTransform = std::make_shared<CTransform>(
        Vec2(windowSize.x / 2, windowSize.y / 2),
        Vec2(playerConfig.Speed, playerConfig.Speed),
        0.0f);

    player->cShape->circle.setPosition(windowSize.x / 2, windowSize.y / 2);
}

void Game::sEnemySpawner()
{
    // do not spawn an enemy each frame
    if (currentFrame <= lastEnemySpawnTime + enemyConfing.SpawnCooldown) {
        return;
    }

    lastEnemySpawnTime = currentFrame;

    std::srand(std::time(nullptr));
    float cx = randRange(
        (float)enemyConfing.ShapeRadius,
        window.getSize().x - (float)enemyConfing.ShapeRadius);
    float cy = randRange(
        (float)enemyConfing.ShapeRadius,
        window.getSize().y - (float)enemyConfing.ShapeRadius);
    int vertices = randRange(enemyConfing.MinVertices, enemyConfing.MaxVertices);
    Color fill = {
        .R = randRange(255),
        .G = randRange(255),
        .B = randRange(255),
    };
    float speed = randRange(enemyConfing.MinSpeed, enemyConfing.MaxSpeed);

    float teta = fromRad(randRange((float)(2 * M_PI)));
    auto enemy = entities.addEntity("big-enemy");

    enemy->cTransform = std::make_shared<CTransform>(
        Vec2(cx, cy),
        Vec2::FromSpeedAndAngle(speed, teta),
        teta);

    enemy->cShape = std::make_shared<CShape>(
        enemyConfing.ShapeRadius,
        vertices,
        sf::Color(fill.R, fill.G, fill.B),
        sf::Color(
            enemyConfing.OutlineColor.R,
            enemyConfing.OutlineColor.G,
            enemyConfing.OutlineColor.B),
        enemyConfing.OutlineThickness);

    enemy->cScore = std::make_shared<CScore>(vertices * 100);
    enemy->cCollision = std::make_shared<CCollision>(enemyConfing.CollisionRadius);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    if (entity->cShape == nullptr || entity->cTransform == nullptr)
    {
        return;
    }

    size_t vertices = entity->cShape->circle.getPointCount();
    Vec2 origin = entity->cTransform->position;
    float speedLen = entity->cTransform->velocity.length();
    sf::Color fillColor = entity->cShape->circle.getFillColor();
    float teta = (float)(360 / vertices);
    for (size_t i = 0; i < vertices; i++) {
        Vec2 velocity = Vec2::FromSpeedAndAngle(speedLen, teta * i);
        auto small = entities.addEntity("small-entity");
        small->cShape = std::make_shared<CShape>(
            enemyConfing.ShapeRadius / 3,
            vertices,
            fillColor,
            sf::Color(
                enemyConfing.OutlineColor.R,
                enemyConfing.OutlineColor.R,
                enemyConfing.OutlineColor.B
            ),
            enemyConfing.OutlineThickness
        );
        small->cLifespan = std::make_shared<CLifespan>(enemyConfing.SmallLifespan);
        small->cTransform = std::make_shared<CTransform>(
            origin,
            velocity,
            teta
        );
        small->cCollision = std::make_shared<CCollision>(
            enemyConfing.CollisionRadius / 3
        );
        small->cScore = std::make_shared<CScore>(vertices * 200);
    }
}

void Game::sCollision()
{
    auto bullets = entities.getEntities("bullet");
    // check big-enemy collision (player/bullet)
    for (auto bigEnemy : entities.getEntities("big-enemy")) {
        if (std::any_of(bullets.begin(), bullets.end(), [&bigEnemy](auto bullet) {
                bool colliding = bigEnemy->colliding(*bullet);
                if (colliding)
                {
                    bullet->destroy();
                }
                return colliding;
            })) {
            // update score
            if (bigEnemy->cScore != nullptr)
            {
                score.Value += bigEnemy->cScore->score;
            }
            // destroy bigEnemy and sapwn little enemies
            bigEnemy->destroy();
            spawnSmallEnemies(bigEnemy);
        }

        // destroy player and respawn in the middle
        if (bigEnemy->colliding(*player)) {
            player->destroy();
            spawnPlayer();
        }
    }
    // check small-enemy collision (player/bullet)
    for (auto smallEnemy : entities.getEntities("small-enemy")) {
        if (std::any_of(bullets.begin(), bullets.end(), [&smallEnemy](auto bullet) {
                bool colliding = smallEnemy->colliding(*bullet);
                if (colliding)
                {
                    bullet->destroy();
                }
                return colliding;
            })) {
            // update score
            if (smallEnemy->cScore != nullptr)
            {
                score.Value += smallEnemy->cScore->score;
            }
            // destroy bigEnemy and sapwn little enemies
            smallEnemy->destroy();
        }

        // destroy player and respawn in the middle
        if (smallEnemy->colliding(*player)) {
            player->destroy();
            spawnPlayer();
        }
    }
}

int Game::run()
{
    spawnPlayer();
    while (window.isOpen()) {
        currentFrame++;
        entities.update();
        sUserInput();

        if (!paused) {
            sCollision();
            sMovement();
            sLifespan();
            sEnemySpawner();
        }

        sRender();
    }
    return 0;
}

sf::Font fromConfigs(const FontConfig& configs)
{
    sf::Font font;
    if (!font.loadFromFile(configs.File)) {
        throw FontNotFound {
            .Message = "Font " + configs.File + " not found",
        };
    }
    return font;
}
}
