#include "GameField.h"
#include"Block_factory.h"
#include "element_factory.h"
#include "constant.h"
#include <cstdlib> 
#include "Ball.h"

void GameField::initLevel() {
    clear();

    // Вычисляем начальный отступ по X, чтобы центрировать сетку блоков
    // 10 блоков по (BLOCK_WIDTH + 10) занимают около 700 пикселей.
    // На экране 1024 отступ в 160 пикселей сделает сетку идеально ровной.
    float startX = 160.0f;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 10; ++j) {
            int chance = rand() % 4; // Число от 0 до 99

            float x = startX + j * (BLOCK_WIDTH + 10.0f);
            float y = 60.0f + i * (BLOCK_HEIGHT + 10.0f); // Чуть опустим сетку вниз

            if (chance == 1) {
                elements_block.push_back(BlockFactory::createElement(BlockFactory::Type::SpeedBlock, x, y,1));
            }
            else if(chance==2){
                elements_block.push_back(BlockFactory::createElement(BlockFactory::Type::hp_block, x, y, 3));
            }
            else if (chance == 3) {
                elements_block.push_back(BlockFactory::createElement(BlockFactory::Type::unbr_block, x, y, -1));
            }
            else if (chance == 0) {
                elements_block.push_back(BlockFactory::createElement(BlockFactory::Type::StandardBlock, x, y, 1));
            }
        }
    }
}



void GameField::checkCollisions_padel(const sf::FloatRect& objectBounds, GameContext& context) {
    // Вектор для сбора позиций уничтоженных блоков на этом кадре

    for (auto& element : elements) {
        if (element && element->isActive()) {
            if (objectBounds.findIntersection(element->getBounds())) {
                sf::Vector2f pos = element->getPosition();

                element->activate(context);
            }
        }
    }
  
}

void GameField::checkCollisions_ball(Ball& ball, const sf::FloatRect& objectBounds, GameContext& context) {
    // Вектор для сбора позиций уничтоженных блоков на этом кадре
    std::vector<sf::Vector2f> brokenBlockPositions;

    for (auto& element_block : elements_block) {
        if (element_block && element_block->isActive()) {

            // Если произошло столкновение мяча с блоком
            if (objectBounds.findIntersection(element_block->getBounds())) {
                sf::Vector2f pos = element_block->getPosition();

                // 1. Заставляем мяч отскочить по правильной траектории
                ball.handleBlockCollision(element_block->getBounds());

                // 2. Активируем логику блока (нанесение урона / триггер эффекта)
                element_block->activate(context);

                // Если после удара блок разрушился, запоминаем его координаты для бонуса
                if (!element_block->isActive()) {
                    brokenBlockPositions.push_back(pos);
                }

                // Прерываем цикл на этом кадре для этого конкретного мяча, 
                // чтобы он не обработал отскок сразу от двух блоков одновременно
                break;
            }
        }
    }

    // Рождаем бонусы на месте сломанных блоков
    for (const auto& pos : brokenBlockPositions) {
        spawnRandomBonus(pos.x + BLOCK_WIDTH / 2.0f, pos.y + BLOCK_HEIGHT / 2.0f);
    }
}


void GameField::update() {
    // 1. Обновляем обычные динамические элементы (мяч, бонусы)
    for (auto& element : elements) {
        if (element && element->isActive()) {
            element->update();
        }
    }

    // 2. Очищаем удаленные динамические элементы
    elements.erase(
        std::remove_if(elements.begin(), elements.end(),
            [](const std::unique_ptr<BaseElement>& el) { return !el->isActive(); }),
        elements.end()
    );

    // 3. Очищаем только разрушенные блоки (у которых isActive() вернул false)
    elements_block.erase(
        std::remove_if(elements_block.begin(), elements_block.end(),
            [](const std::unique_ptr<base_block>& el) { return !el->isActive(); }),
        elements_block.end()
    );
}



void GameField::draw(sf::RenderWindow& window) {
    for (auto& element : elements) {
        if (element) {
            element->draw(window);
        }
    }
    for (auto& element_block : elements_block) {
        if (element_block) {
            element_block->draw(window);
        }
    }
}

void GameField::clear() {
    elements.clear();
}

void GameField::spawnRandomBonus(float x, float y) {
    int chance = rand() % 5; // Число от 0 до 99

    if (chance ==0) { // 15% шанс на выпадение бонуса размера (Тип 5)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::SizeBonus, x, y));
    }
    else if (chance ==1) { // 10% шанс на выпадение одноразового дна (Тип 6)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::BottomBonus, x, y));
    }
    else if (chance == 2) { // 10% шанс на изменение траектории (Тип 7)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::TrajectoryBonus, x, y));
    }
    else if (chance == 3) { // 10% шанс на изменение траектории (Тип 7)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::SpeedBonus, x, y));
    }
    else if (chance == 4) { // 10% шанс на изменение траектории (Тип 7)
        elements.push_back(ElementFactory::createElement(ElementFactory::Type::StickBonus, x, y));
    }
    // В остальных 65% случаев ничего не выпадает
}