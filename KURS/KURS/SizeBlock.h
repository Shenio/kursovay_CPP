#pragma once
#include "Base_element.h"

class SizeBlock : public BaseElement {
private:
    sf::RectangleShape shape; // У блока прямоугольная форма!
public:
    SizeBlock(float x, float y);
    void activate(GameContext& context) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
