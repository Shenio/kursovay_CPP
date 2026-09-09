#include "StickBonus.h"
#include "constant.h"
#include "game_contex.h"

StickBonus::StickBonus(float x, float y) : BaseElement(x, y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White); // Пусть дно будет зеленым
}

void StickBonus::update() {
    if (isActive()) {
        position.y += BONUS_DROP_SPEED;
        shape.setPosition(position);
    }
}

void StickBonus::activate(GameContext& context) {
    context.ballSticky = true; // Активируем защиту от падения (Тип 6)
    deactivate();
}

void StickBonus::draw(sf::RenderWindow& window)const {
    if (isActive()) window.draw(shape);
}

sf::FloatRect StickBonus::getBounds() const {
    return shape.getGlobalBounds();
}
