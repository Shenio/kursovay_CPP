#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

// Опережающее объявление контекста игры, чтобы элементы могли менять состояние игры
class GameContext;

class BaseElement {
protected:
    sf::Vector2f position;
    bool active = true;

public:
    BaseElement(float x, float y);
    virtual ~BaseElement() = default;

    // Внутри класса BaseElement в файле BaseElement.h:
    virtual void activate(GameContext& context) = 0;

    virtual void update() {}

    // Отрисовка элемента на экране
    virtual void draw(sf::RenderWindow& window) = 0;

    // Получение границ для проверки коллизий
    virtual sf::FloatRect getBounds() const = 0;

    bool isActive() const { return active; }
    void deactivate() { active = false; }

    void setPosition(const sf::Vector2f& pos) { position = pos; }
    sf::Vector2f getPosition() const { return position; }
};
