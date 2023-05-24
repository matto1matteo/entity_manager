#pragma once

#include <string>
#include <game/color.hpp>

namespace mtt
{

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
    Color FontColor;
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
    
}
