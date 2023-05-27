#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <game/game_configs.hpp>

namespace mtt {

class Score {
public:
    sf::Text        Text;
    unsigned int    Value = 0;

    Score() = default;
    ~Score() = default;
    Score(Score && s) = default;
    Score(const Score & s) = default;
    Score(
        const sf::Font & font,
        const sf::Color & fillColor,
        unsigned int charSize = 22
    );

    void updateText();
    void updateText(unsigned int value);
    void setUp(const sf::Font & font, unsigned int size, const mtt::Color & color);

private:
    std::string TEXT = "SCORE ";
};

}
