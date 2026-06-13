#include "Ball.h"
#include "constant.h"
#include <cmath>

Ball::Ball(float x, float y) {
    shape.setRadius(BALL_RADIUS);
    shape.setOrigin({ BALL_RADIUS, BALL_RADIUS });
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color::White);
    velocity = { -INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED }; // Движение вверх-влево
}

bool Ball::update(float windowWidth, float windowHeight) {
    shape.move(velocity);
    sf::Vector2f pos = shape.getPosition();

    // Отскок от левой и правой стен
    if (pos.x - BALL_RADIUS < 0 || pos.x + BALL_RADIUS > windowWidth) {
        bounceX();
    }
    // Отскок от верхней стены
    if (pos.y - BALL_RADIUS < 0) {
        bounceY();
    }

    // Если мяч упал за нижний край (мимо ракетки)
    if (pos.y + BALL_RADIUS > windowHeight) {
        return true; // Сигнализируем в main.cpp, что мяч улетел вниз
    }

    return false; // Мяч всё еще летает в пределах поля
}

// 1. Обновляем метод изменения скорости (делаем лимит жестче)
void Ball::setSpeedMultiplier(float factor) {
    // Ограничиваем максимальное ускорение на уровне 1.6, чтобы мяч не летал слишком быстро
    if (factor > 1.6f) {
        factor = 1.6f;
    }

    float angle = atan2(velocity.y, velocity.x);
    // Берем уменьшенную базовую скорость, чтобы играть было комфортно
    float speed = INITIAL_BALL_SPEED * factor;

    velocity.x = cos(angle) * speed;
    velocity.y = sin(angle) * speed;
}

// 2. Добавляем умный отскок по Y, который выталкивает мяч вверх
void Ball::bounceY() {
    velocity.y = -velocity.y; // Меняет направление на противоположное
}

void Ball::bounceX() {
    velocity.x = -velocity.x;
}



void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}
void Ball::setPosition(float x, float y) {
    shape.setPosition({ x, y });
}
void Ball::setRandomAngle(float angleRadians) {
    // Вычисляем текущую абсолютную скорость мяча
    float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    // Задаем новые направления вектора по случайному углу
    velocity.x = cos(angleRadians) * speed;
    velocity.y = sin(angleRadians) * speed;
}
void Ball::setCustomVelocity(float vx, float vy) {
    velocity.x = vx;
    velocity.y = vy;
}



