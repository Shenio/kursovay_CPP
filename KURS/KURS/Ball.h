#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Ball(float x, float y);
    void setPosition(float x, float y);
    bool update(float windowWidth, float windowHeight);
    void bounceY();
    void bounceX();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setRandomAngle(float angleRadians);

    void setSpeedMultiplier(float factor);
    sf::Vector2f getVelocity() const { return velocity; }
    void setCustomVelocity(float vx, float vy);


    void handleBlockCollision(const sf::FloatRect& blockBounds);

};
