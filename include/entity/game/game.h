#pragma once
#include <SFML/Graphics.hpp>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <memory>
#include <string>

struct Color {
    int R, G, B;
};

/// @brief  `WindowConfig` is a data struct that holds the configurations for the
///         window
struct WindowConfig {
    int Width;
    int Height;
    int FrameRateLimit;
    bool FullScreen;
};

/// @brief `FontConfig` data structure holding font configuration data
struct FontConfig {
    std::string File;
    int Size;
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
/// enemies will spawn in place of the original enemy, with the same N
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
    int SmallLifespan;
    int SpawnCooldown;
};

/// @brief  `BulletConfig` data structure used to hold the configuration data of
///         player bullets
struct BulletConfig {
    int ShapeRadius;
    int CollisionRadius;
    float Speed;
    Color FillColor;
    Color OutlineColor;
    int OutlineThickness;
    int Lifespan;
};

/// Special ability
struct SpecialConfig {
    int CoolDown;
};

struct ConfigException {
    std::string Message;
};

/// A Score component will be assigned to each enemy and value of the score
/// will be equal to N * 100 for big enemies and N * 200 for small eneemies
/// where N is the number of vertices of the enemy.
///
/// `ESC` will close the game
/// `P` will pause the game
class Game {

private:
    sf::RenderWindow m_window;
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


/// @brief  `toggleFullScreen` will toggle `window` to and from a full screen
///         status
///
/// @param  `window` the SFML window to resize
/// @param  `isFullScreen` tells wheter the window was previously in a full
///         screen state or not
/// @param  `originalSize` represents the video mode of the window when non
///         in full screen
void toggleFullScreen(sf::RenderWindow & window, bool isFullScreen, const sf::VideoMode & originalSize);
