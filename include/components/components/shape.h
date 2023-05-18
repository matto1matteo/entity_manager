#pragma once
#include <SFML/Graphics.hpp>

class CShape {
public:
    sf::CircleShape circle;

    CShape(float radius,
           int point,
           const sf::Color & fill,
           const sf::Color & outline,
           float thickness)
        : circle(radius, point)
    {
        circle.setFillColor(fill);
        circle.setOutlineThickness(thickness);
        circle.setOutlineColor(outline);
        circle.setOrigin(radius, radius);
    }


private:
    
};
