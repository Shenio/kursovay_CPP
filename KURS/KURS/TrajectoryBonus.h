#pragma once
#include "Base_element.h"

class TrajectoryBonus : public BaseElement {
private:
    sf::CircleShape shape;

public:
    TrajectoryBonus(float x, float y);
    void update() override;
    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
