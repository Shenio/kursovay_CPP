#include "unbr_block.h"
#include "constant.h"
#include "game_contex.h"

unbr_block::unbr_block(float x, float y, int hp) :base_block(x, y, hp) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}


void unbr_block::activate(GameContext& context) {

}

void unbr_block::draw(sf::RenderWindow& window) const {
    if (isActive()) {
        window.draw(shape);
    }
}

sf::FloatRect unbr_block::getBounds() const {
    return shape.getGlobalBounds();
}

