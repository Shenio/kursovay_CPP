#pragma once
#include "Base_element.h"

class BottomBonus : public BaseElement {
private:
    sf::CircleShape shape;

public:
    BottomBonus(float x, float y);
    void update() override;
    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
};
