#pragma once
#include "Base_element.h"

class SpeedBlock : public BaseElement {
private:
    sf::RectangleShape shape;

public:
    SpeedBlock(float x, float y);
    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
