#include "StandartBlock.h"
#include "constant.h"
#include "game_contex.h"

StandardBlock::StandardBlock(float x, float y, int hp) :base_block(x, y, hp){
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red); 
}


void StandardBlock::activate(GameContext& context) {
    health--;
    context.playerScore += 10; // Добавляем очки через контекст
    if (health <= 0) {
        deactivate(); // Помечаем блок как неактивный (разрушен)
    }
}

void StandardBlock::draw(sf::RenderWindow& window) const {
    if (isActive()) {
        window.draw(shape);
    }
}

sf::FloatRect StandardBlock::getBounds() const {
    return shape.getGlobalBounds();
}

