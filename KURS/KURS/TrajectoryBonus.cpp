#include "TrajectoryBonus.h"
#include "constant.h"
#include "game_contex.h"

TrajectoryBonus::TrajectoryBonus(float x, float y) : BaseElement(x, y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Cyan); // Бирюзовый цвет для траектории
}

void TrajectoryBonus::update() {
    if (isActive()) {
        position.y += BONUS_DROP_SPEED;
        shape.setPosition(position);
    }
}

void TrajectoryBonus::activate(GameContext& context) {
    context.triggerRandomTrajectory = true; // Взводим триггер для изменения угла (Тип 7)
    deactivate();
}

void TrajectoryBonus::draw(sf::RenderWindow& window) {
    if (isActive()) window.draw(shape);
}

sf::FloatRect TrajectoryBonus::getBounds() const {
    return shape.getGlobalBounds();
}
