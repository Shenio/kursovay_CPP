#include "Paddle.h"
#include "constant.h"

Paddle::Paddle(float x, float y) : speed(INITIAL_PADDLE_SPEED) {
    shape.setSize({ 120.0f, PADDLE_HEIGHT }); // Начальная ширина
    shape.setOrigin({ shape.getSize().x / 2.0f, shape.getSize().y / 2.0f });
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color::Blue);
}

void Paddle::update(float windowWidth) {
    sf::Vector2f pos = shape.getPosition();
    float halfWidth = shape.getSize().x / 2.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && pos.x - halfWidth > 0) {
        shape.move({ -speed, 0.0f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && pos.x + halfWidth < windowWidth) {
        shape.move({ speed, 0.0f });
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::setWidth(float width) {
    sf::Vector2f pos = shape.getPosition();
    shape.setSize({ width, PADDLE_HEIGHT });
    shape.setOrigin({ width / 2.0f, PADDLE_HEIGHT / 2.0f });
    shape.setPosition(pos);
}
