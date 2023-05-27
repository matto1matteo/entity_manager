#include <game/score.hpp>

namespace mtt
{
Score::Score(
    const sf::Font & font,
    const sf::Color & fillColor,
    unsigned int charSize
)
{
    Text.setFont(font);
    Text.setFillColor(fillColor);
    Text.setCharacterSize(charSize);
    updateText();
}

void Score::updateText(unsigned int value)
{
    Value = value;
    updateText();
}

void Score::updateText()
{
    Text.setString(TEXT + std::to_string(Value));
}
void Score::setUp(const sf::Font & font, unsigned int size, const mtt::Color & color)
{
    Text.setFont(font);
    Text.setCharacterSize(size);
    Text.setFillColor(sf::Color(
        color.R,
        color.G,
        color.B
    ));
}
}
