#pragma once
#include "Base_element.h"

class StandardBlock : public BaseElement {
private:
    sf::RectangleShape shape;
    int health;

public:
    StandardBlock(float x, float y, int hp = 1);

    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
