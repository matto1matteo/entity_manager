#include <game/window.hpp>

namespace mtt {
Window::Window(sf::VideoMode mode, const std::string& title)
{
    window.create(mode, title);
}

Window::Window(const WindowConfig& config)
    : fullScreen(config.FullScreen)
    , mode(sf::VideoMode(config.Width, config.Height))
{
    toggleFullScreen();
    window.setFramerateLimit(config.FrameRateLimit);
}

void Window::clear(const sf::Color &color)
{
    window.clear(color);
}

inline void Window::create()
{
    if (fullScreen)
    {
        window.create(
            sf::VideoMode::getDesktopMode(),
            "EntityManager",
            sf::Style::Fullscreen);
    }
    else
    {
        window.create(
            mode,
            "EntityManager",
            sf::Style::Default);
    }
}

void Window::create(const WindowConfig& config)
{
    fullScreen = config.FullScreen;
    mode = sf::VideoMode(config.Width, config.Height);
    create();
    window.setFramerateLimit(config.FrameRateLimit);
}

void Window::create(sf::VideoMode mode, const std::string& title)
{
    window.create(mode, title);
}

void Window::toggleFullScreen()
{
    fullScreen = !fullScreen;
    create();
}

void Window::draw(const sf::Drawable & drowable)
{
    window.draw(drowable);
}

Vec2 Window::getSize() const
{
    auto size = window.getSize();
    return Vec2(size.x, size.y);
}

bool Window::overflowX(const Entity & entity) const
{
    float windowWidth = getSize().x;
    float radius = entity.cShape->circle.getRadius();
    Vec2 position = entity.cTransform->position;
    return position.x + radius >= windowWidth;
}

bool Window::underflowX(const Entity & entity) const
{
    float radius = entity.cShape->circle.getRadius();
    Vec2 position = entity.cTransform->position;
    return position.x - radius <= 0;
}

bool Window::overflowY(const Entity & entity) const
{
    float windowHeight = getSize().y;
    float radius = entity.cShape->circle.getRadius();
    Vec2 position = entity.cTransform->position;
    return position.y + radius >= windowHeight;
}

bool Window::underflowY(const Entity & entity) const
{
    float radius = entity.cShape->circle.getRadius();
    Vec2 position = entity.cTransform->position;
    return position.y - radius <= 0;
}
}
