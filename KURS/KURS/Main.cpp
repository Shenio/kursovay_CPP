#include <SFML/Graphics.hpp>
#include "constant.h"
#include "game_contex.h"
#include "GameField.h"
#include "Paddle.h"
#include "Ball.h"
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Arcanoid with SFML 3");

    // Игровые объекты
    GameField field;
    field.initLevel();

    Paddle paddle(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 50.0f);
    Ball ball(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 100.0f);

    // Параметры для контекста игры
    float currentBallSpeed = 1.0f; // Коэффициент скорости
    float currentPaddleWidth = 120.0f;
    bool ballSticky = false;
    bool oneTimeBottom = false;
    int score = 0;
    bool triggerTrajectory = false;

    // ОБЯЗАТЕЛЬНО ДОБАВИТЬ ТУТ:
    bool isGameStarted = false;

    // Создаем контекст
    GameContext context{
        currentBallSpeed,
        currentPaddleWidth,
        ballSticky,
        oneTimeBottom,
        score,
        triggerTrajectory
    };


    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // 1. Обновление физики и управления
        paddle.update(static_cast<float>(WINDOW_WIDTH));
        // Проверяем, запущена ли игра (если нет — мяч ждет на ракетке)
        if (!isGameStarted) {
            sf::FloatRect pBounds = paddle.getBounds();
            // Пересоздаем мяч строго по центру ракетки
            ball = Ball(pBounds.position.x + pBounds.size.x / 2.0f, pBounds.position.y - BALL_RADIUS - 4.0f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                isGameStarted = true;
            }
        }

        else {
            // Если бонус траектории был пойман (Тип 7)
            if (context.triggerRandomTrajectory) {
                context.triggerRandomTrajectory = false;

                // Генерируем случайный угол в радианах (примерно от 45 до 135 градусов, чтобы летел вверх)
                float randomAngle = -(3.14159f / 4.0f + (rand() % 100 / 100.0f) * (3.14159f / 2.0f));
                ball.setRandomAngle(randomAngle); // Этот метод добавим в класс Ball ниже
            }

            ball.setSpeedMultiplier(context.ballSpeed);

            // Логика падения и одноразового дна (Тип 6)
            if (ball.update(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT))) {
                if (context.oneTimeBottom) {
                    ball.bounceY();
                    context.oneTimeBottom = false; // Дно использовано
                }
                else {
                    isGameStarted = false;
                    context.ballSpeed = 1.0f;
                    context.paddleWidth = 120.0f;
                }
            }
        }


        field.update();

        // 2. Обработка коллизий с ракеткой
                // 2. Обработка коллизий с ракеткой
        if (ball.getBounds().findIntersection(paddle.getBounds())) {
            sf::FloatRect pBounds = paddle.getBounds();
            sf::FloatRect bBounds = ball.getBounds();

            // 1. Выталкиваем мяч НАД ракеткой, чтобы исключить застревание
            ball.setPosition(bBounds.position.x, pBounds.position.y - BALL_RADIUS - 2.0f);

            // 2. Находим центры мяча и ракетки по горизонтали
            float ballCenter = bBounds.position.x + bBounds.size.x / 2.0f;
            float paddleCenter = pBounds.position.x + pBounds.size.x / 2.0f;

            // 3. Вычисляем относительную точку удара (от -1.0 на левом краю до 1.0 на правом)
            float relativeHitPos = (ballCenter - paddleCenter) / (pBounds.size.x / 2.0f);

            // Ограничиваем значения, чтобы они не выходили за пределы [-1, 1]
            if (relativeHitPos < -1.0f) relativeHitPos = -1.0f;
            if (relativeHitPos > 1.0f)  relativeHitPos = 1.0f;

            // 4. Задаем максимальный угол отклонения от вертикали (около 60 градусов)
            float maxAngle = 60.0f * (3.14159f / 180.0f);
            float hitAngle = relativeHitPos * maxAngle;

            // 5. Передаем новый угол в мяч (угол hitAngle откладывается от вертикали вверх)
            // Новый вектор направления полета:
            float speed = sqrt(ball.getVelocity().x * ball.getVelocity().x + ball.getVelocity().y * ball.getVelocity().y);

            // Задаем компоненты скорости (sin дает смещение по X, а -cos направляет строго ВВЕРХ)И
            ball.setCustomVelocity(sin(hitAngle) * speed, -cos(hitAngle) * speed);
        }




        // 3. Обработка коллизий с элементами поля (блоки и бонусы)
        // Если мяч касается блока, блок через context начислит очки и разрушится
        sf::FloatRect ballBounds = ball.getBounds();
        field.checkCollisions(ballBounds, context);

        // Также проверяем, не поймала ли ракетка падающий бонус
        sf::FloatRect paddleBounds = paddle.getBounds();
        field.checkCollisions(paddleBounds, context);

        // Применяем изменения из контекста (если бонус сработал)
        paddle.setWidth(currentPaddleWidth);

        // 4. Отрисовка кадра
        window.clear(sf::Color::Black);

        field.draw(window);
        paddle.draw(window);
        ball.draw(window);

        window.display();
    }

    return 0;
}
