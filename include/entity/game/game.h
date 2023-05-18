#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <entity/entity_manager.h>
#include <entity/entity.h>

struct PlayerConfig {};
struct EnemyConfig {};
struct BulletConfig {};

class Game {

private:
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;

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
    /// `init` read configuration file `config_file` and set up game 
    /// options
    void init(std::string config_file);

    /// `setPaused` set the paused flag
    void setPaused(bool paused);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & pos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

    Game(std::string config_file);
    int run();

};
