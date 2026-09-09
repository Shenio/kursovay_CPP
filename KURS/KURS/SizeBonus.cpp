#include "SizeBonus.h"
#include "constant.h"
#include "game_contex.h"

SizeBonus::SizeBonus(float x, float y) : BaseElement(x, y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Yellow); // Бонус будет желтым кружком
}

void SizeBonus::update() {
    if (isActive()) {
        position.y += BONUS_DROP_SPEED;
        shape.setPosition(position);
    }
}

void SizeBonus::activate(GameContext& context) {
    context.paddleWidth = 250.0f; // Увеличиваем каретку (Тип 5 из ТЗ)
    deactivate();
}

void SizeBonus::draw(sf::RenderWindow& window)const  {
    if (isActive()) window.draw(shape);
}

sf::FloatRect SizeBonus::getBounds() const {
    return shape.getGlobalBounds();
}
