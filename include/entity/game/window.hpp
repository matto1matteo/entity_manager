#pragma once
#include <SFML/Graphics.hpp>

#include <game/game_configs.hpp>

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

    bool isFullScreen() const { return fullScreen; }

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

