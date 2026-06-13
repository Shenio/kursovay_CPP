#pragma once
#include "Base_element.h"

class SizeBonus : public BaseElement {
private:
    sf::CircleShape shape;

public:
    SizeBonus(float x, float y);
    void update() override;
    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
