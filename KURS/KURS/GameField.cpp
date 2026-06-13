#include "GameField.h"
#include "element_factory.h"
#include "constant.h"
#include <cstdlib> 
void GameField::initLevel() {
    clear();

    // Вычисляем начальный отступ по X, чтобы центрировать сетку блоков
    // 10 блоков по (BLOCK_WIDTH + 10) занимают около 700 пикселей.
    // На экране 1024 отступ в 160 пикселей сделает сетку идеально ровной.
    float startX = 160.0f;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            float x = startX + j * (BLOCK_WIDTH + 10.0f);
            float y = 60.0f + i * (BLOCK_HEIGHT + 10.0f); // Чуть опустим сетку вниз

            if (i == 1) {
                elements.push_back(ElementFactory::createElement(ElementFactory::Type::SizeBlock, x, y));
            }
            else {
                elements.push_back(ElementFactory::createElement(ElementFactory::Type::Standard, x, y));
            }
        }
    }
}



void GameField::checkCollisions(const sf::FloatRect& objectBounds, GameContext& context) {
    // Вектор для сбора позиций уничтоженных блоков на этом кадре
    std::vector<sf::Vector2f> brokenBlockPositions;

    for (auto& element : elements) {
        if (element && element->isActive()) {
            if (objectBounds.findIntersection(element->getBounds())) {
                sf::Vector2f pos = element->getPosition();

                element->activate(context);

                
                if (!element->isActive()) {
                    brokenBlockPositions.push_back(pos);
                }
            }
        }
    }

    // Рождаем бонусы на месте сломанных блоков
    for (const auto& pos : brokenBlockPositions) {
        spawnRandomBonus(pos.x + BLOCK_WIDTH / 2.0f, pos.y + BLOCK_HEIGHT / 2.0f);
    }
}


void GameField::update() {
    for (auto& element : elements) {
        if (element && element->isActive()) {
            element->update();
        }
    }


    elements.erase(
        std::remove_if(elements.begin(), elements.end(),
            [](const std::unique_ptr<BaseElement>& el) { return !el->isActive(); }),
        elements.end()
    );
}


void GameField::draw(sf::RenderWindow& window) {
    for (auto& element : elements) {
        if (element) {
            element->draw(window);
        }
    }
}

void GameField::clear() {
    elements.clear();
}

void GameField::spawnRandomBonus(float x, float y) {
    int chance = rand() % 100; // Число от 0 до 99

    if (chance < 15) { // 15% шанс на выпадение бонуса размера (Тип 5)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::SizeBonus, x, y));
    }
    else if (chance >= 15 && chance < 25) { // 10% шанс на выпадение одноразового дна (Тип 6)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::BottomBonus, x, y));
    }
    else if (chance >= 25 && chance < 35) { // 10% шанс на изменение траектории (Тип 7)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::TrajectoryBonus, x, y));
    }
    // В остальных 65% случаев ничего не выпадает
}