#pragma once
#include <SFML/Graphics.hpp>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <memory>
#include <string>

struct Color {
    int R, G, B;
};

/// The player spawn at the center at the start and whenever it dies
/// Moves by Speed in the derections specificed by the controls (wasd)
/// Can moove only inside the bound of the window
/// Left click from mouse trigger a bullet to spawn in the dirction of the mouse
/// Right click from mouse trigger the special ability
struct PlayerConfig {
    int ShapeRadius;
    int CollisionRadius;
    float Speed;
    Color FillColor;
    Color OutlineColor;
    int OutlineThickness;
    int Vertices;
};

/// Enemy spawn in a random locations every SpawnCooldown in the bounding box of
/// the window
/// Each enemy will have a random number of vertices between MinVertices and
/// MaxVertices
/// Will be given a random color
/// Will be given a random speed between MinSpeed and MaxSpeed
/// Enemy will bounce on the window bounding box
/// When a large enemies collide with a bullet N (number of vertices) small
/// enemies will spawn in place of the original enemies, with the same N
/// vertices of the original one with angles of a fixed value equal to 360/N.
struct EnemyConfig {
    int ShapeRadius;
    int CollisionRadius;
    float MinSpeed;
    float MaxSpeed;
    Color OutlineColor;
    int OutlineThickness;
    int MinVertices;
    int MaxVertices;
    int SmallLifeSpan;
    int SpawnCooldown;
};

struct BulletConfig {
    int ShapeRadius;
    int CollisionRadius;
    float Speed;
    Color FillColor;
    Color OutlineColor;
    int OutlineThickness;
    int LifeSpan;
};

/// Special ability
struct SpecialConfig {
    int CoolDown;
};

/// `WindowConfig` is a data struct that holds the configurations for the
/// window
struct WindowConfig {
    int Width;
    int Height;
    int FrameRateLimit;
    bool FullScreen;
};

struct FontConfig {
    std::string File;
    int Size;
    int R, G, B;
};

/// `ESC` will close the game
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

    /// when hitting `p` `setPaused` set the paused flag
    void setPaused(bool paused);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
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
