#include "SpeedBlock.h"
#include "constant.h"
#include "game_contex.h"

SpeedBlock::SpeedBlock(float x, float y) : BaseElement(x, y) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Magenta); // Выделим его фиолетовым цветом
}

void SpeedBlock::activate(GameContext& context) {
    context.ballSpeed *= 1.2f; // Увеличиваем скорость шарика при столкновении (Тип 3)
    context.playerScore += 5;
    deactivate(); // Блок уничтожается
}

void SpeedBlock::draw(sf::RenderWindow& window) {
    if (isActive()) window.draw(shape);
}

sf::FloatRect SpeedBlock::getBounds() const {
    return shape.getGlobalBounds();
}
