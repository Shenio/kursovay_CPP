#include "SpeedBlock.h"
#include "constant.h"
#include "game_contex.h"



SpeedBlock::SpeedBlock(float x, float y,int hp) :base_block(x, y, hp) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Magenta); // Выделим его фиолетовым цветом
}

void SpeedBlock::activate(GameContext& context) {
    context.ballSpeed *= 1.2f; // Увеличиваем скорость шарика при столкновении (Тип 3)
    health--;
    context.playerScore += 5; // Добавляем очки через контекст
    if (health <= 0) {
        deactivate(); // Помечаем блок как неактивный (разрушен)
    }
}

void SpeedBlock::draw(sf::RenderWindow& window)const {
    if (isActive()) window.draw(shape);
}

sf::FloatRect SpeedBlock::getBounds() const {
    return shape.getGlobalBounds();
}
