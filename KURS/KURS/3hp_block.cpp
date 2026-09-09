#include "3hp_block.h"
#include "constant.h"
#include "game_contex.h"

hp_block::hp_block(float x, float y, int hp) :base_block(x, y, hp) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);
}


void hp_block::activate(GameContext& context) {
    health--;
    context.playerScore += 2; // Добавляем очки через контекст
    if (health <= 0) {
        deactivate(); // Помечаем блок как неактивный (разрушен)
    }
}

void hp_block::draw(sf::RenderWindow& window) const {
    if (isActive()) {
        window.draw(shape);
    }
}

sf::FloatRect hp_block::getBounds() const {
    return shape.getGlobalBounds();
}

