#pragma once
#include <SFML/Graphics.hpp>

#include <game/game_configs.hpp>
#include <geometry/vec2.h>
#include <entity/entity.h>

namespace mtt {

class Window {
public:
    Window() = default;
    Window(sf::VideoMode mode, const std::string & title);
    Window(const WindowConfig & config);
    ~Window() = default;

    void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
    void display() { window.display(); }
    void create(const WindowConfig & config);
    void create(sf::VideoMode mode, const std::string & title);
    bool isOpen() const { return window.isOpen(); }
    bool pollEvent(sf::Event & event) { return window.pollEvent(event); }
    void close() { window.close(); }
    void draw(const sf::Drawable & drowable);
    Vec2 getSize() const;

    bool isFullScreen() const { return fullScreen; }

    /// @brief  Tells if the given entity is overflowing on the x axis
    ///         of the window
    /// @param  entity  the entity that we would like to test against
    bool overflowX(const Entity & entity) const;

    /// @brief  Tells if the given entity is underflowing on the x axis
    ///         of the window
    /// @param  entity  the entity that we would like to test against
    bool underflowX(const Entity & entity) const;

    /// @brief  Tells if the given entity is overflowing on the y axis
    ///         of the window
    /// @param  entity  the entity that we would like to test against
    bool overflowY(const Entity & entity) const;

    /// @brief  Tells if the given entity is underflowing on the y axis
    ///         of the window
    /// @param  entity  the entity that we would like to test against
    bool underflowY(const Entity & entity) const;

    /// @brief  `toggleFullScreen` will toggle `window` to and from a full screen
    ///         status
    ///
    /// @param  `window` the SFML window to resize
    /// @param  `isFullScreen` tells wheter the window was previously in a full
    ///         screen state or not
    /// @param  `originalSize` represents the video mode of the window when non
    ///         in full screen
    void toggleFullScreen();

private:
    sf::RenderWindow window;
    sf::VideoMode mode;
    bool fullScreen;

private:
    void create();
};

}

