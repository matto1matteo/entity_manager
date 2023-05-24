#pragma once
#include <SFML/Graphics.hpp>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <memory>
#include <string>
#include <game/game_configs.hpp>
#include <game/window.hpp>


namespace mtt
{

/// A Score component will be assigned to each enemy and value of the score
/// will be equal to N * 100 for big enemies and N * 200 for small eneemies
/// where N is the number of vertices of the enemy.
///
/// `ESC` will close the game
/// `P` will pause the game
class Game {

private:
    mtt::Window window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;

    sf::VideoMode m_originalSize;
    bool m_fullScreen;

    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;

    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;

    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player;

private:
    /// @brief  `init` read configuration file `config_file` and set up game
    ///         options. It will also create the SFML related objects
    void init(std::string config_file);

    /// when hitting `p` `setPaused` set the paused flag
    void setPaused(bool paused);

    /// @brief  Movement system
    void sMovement();

    /// @brief  Input system
    void sUserInput();
    
    /// @brief  Lifespan system system
    void sLifespan();

    /// @brief  Render system
    void sRender();

    /// @brief  Enemy system
    void sEnemySpawner();

    /// @brief  Collision system system
    void sCollision();

    /// To make our lives easier, we will set the origin with `Shape::setOrigin`
    /// to the center of the CircleShape
    void spawnPlayer();
    /// To make our lives easier, we will set the origin with `Shape::setOrigin`
    /// to the center of the CircleShape
    void spawnEnemy();

    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& pos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(std::string config_file);
    int run();
};


    
}
