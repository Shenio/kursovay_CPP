#pragma once

#include "base_block.h"
#include <SFML/Graphics.hpp>

// Опережающее объявление: говорим компилятору, что структура существует.
// Сам файл подключать здесь НЕ НАДО.
class GameContext;

class unbr_block : public base_block {
private:
    sf::RectangleShape shape;

public:
    unbr_block(float x, float y, int hp = -1);

    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) const override; // Убедитесь, что тут есть const!
    sf::FloatRect getBounds() const override;
};
