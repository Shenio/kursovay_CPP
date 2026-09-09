#include "SizeBlock.h"
#include "constant.h"
#include "game_contex.h"

SizeBlock::SizeBlock(float x, float y) : BaseElement(x, y) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Magenta); // Блок будет фиолетовым прямоугольником
}

void SizeBlock::activate(GameContext& context) {
    context.ballSpeed *= 1.2f; // Ускоряем мяч при ударе (Тип 3 из ТЗ)
    context.playerScore += 5;
    deactivate();
}

void SizeBlock::draw(sf::RenderWindow& window) {
    if (isActive()) window.draw(shape);
}

sf::FloatRect SizeBlock::getBounds() const {
    return shape.getGlobalBounds();
}
