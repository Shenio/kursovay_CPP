#include "BottomBonus.h"
#include "constant.h"
#include "game_contex.h"

BottomBonus::BottomBonus(float x, float y) : BaseElement(x, y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Green); // Пусть дно будет зеленым
}

void BottomBonus::update() {
    if (isActive()) {
        position.y += BONUS_DROP_SPEED;
        shape.setPosition(position);
    }
}

void BottomBonus::activate(GameContext& context) {
    context.oneTimeBottom = true; // Активируем защиту от падения (Тип 6)
    deactivate();
}

void BottomBonus::draw(sf::RenderWindow& window) {
    if (isActive()) window.draw(shape);
}

sf::FloatRect BottomBonus::getBounds() const {
    return shape.getGlobalBounds();
}
