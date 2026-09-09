#pragma once
#include <vector>
#include <memory>
#include "Base_element.h"
#include"base_block.h"
#include "game_contex.h"

class Ball;
class GameField {
private:
    // Хранение элементов по указателю базового класса (полиморфизм)
    std::vector<std::unique_ptr<BaseElement>> elements;
    std::vector<std::unique_ptr<base_block>> elements_block;

public:
    GameField() = default;

    // Метод генерации начального уровня с помощью фабрики
    void initLevel();

    // Проверка коллизий с шариком или кареткой
    void checkCollisions_padel(const sf::FloatRect& objectBounds, GameContext& context);
    void checkCollisions_ball(Ball& ball, const sf::FloatRect& objectBounds, GameContext& context);

    // Обновление состояния элементов (например, падение бонусов)
    void update();

    // Отрисовка всех активных элементов поля
    void draw(sf::RenderWindow& window);

    // Очистка поля
    void clear();
    // Внутри класса GameField в секцию private:
    void spawnRandomBonus(float x, float y);

};
