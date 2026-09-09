#include "SpeedBonus.h"
#include "constant.h"
#include "game_contex.h"

SpeedBonus::SpeedBonus(float x, float y) : BaseElement(x, y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue); // Бонус будет желтым кружком
}

void SpeedBonus::update() {
    if (isActive()) {
        position.y += BONUS_DROP_SPEED;
        shape.setPosition(position);
    }
}

void SpeedBonus::activate(GameContext& context) {
    context.ballSpeed *= 0.8f;
    //if(context.ballSpeed <= 0.8f) context.ballSpeed = 0.8f;
    deactivate();
}

void SpeedBonus::draw(sf::RenderWindow& window)const {
    if (isActive()) window.draw(shape);
}

sf::FloatRect SpeedBonus::getBounds() const {
    return shape.getGlobalBounds();
}
