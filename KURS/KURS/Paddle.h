#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;

public:
    Paddle(float x, float y);
    void update(float windowWidth);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setWidth(float width);
};
