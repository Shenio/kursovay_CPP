#include "Cheak_contex.h"
#include "Ball.h"
#include "Paddle.h"
#include "constant.h"
#include <cstdlib> // Нужен для функции rand()

void Cheak_contex::Chek(GameContext& context, Ball& ball, Paddle& paddle) {

    // 1. Если мяч прилип — он не должен падать или отскакивать, 
    // его физику мы полностью заблокировали в основном цикле
    if (context.isBallGlued) {
        return;
    }

    // 2. Случайная траектория
    if (context.triggerRandomTrajectory) {
        context.triggerRandomTrajectory = false;
        float randomAngle = -(3.14159f / 4.0f + (rand() % 100 / 100.0f) * (3.14159f / 2.0f));
        ball.setRandomAngle(randomAngle);
    }

    // 3. Применяем скорость
    ball.setSpeedMultiplier(context.ballSpeed);

    // 4. Логика падения и одноразового дна
    if (ball.update(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT))) {
        if (context.oneTimeBottom) {
            ball.bounceY();
            context.oneTimeBottom = false;
        }
        else {
            context.stickyOffset = 0;
            context.oneTimeBottom = false;
            context.isBallGlued = false;
            context.ballSticky = false;
            context.isGameStarted = false;
            context.playerScore -= 10;
            context.ballSpeed = 1.0f;
            context.paddleWidth = 120.0f;
        }
    }

    // 5. Коллизия с ракеткой и прилипание
    if (ball.getBounds().findIntersection(paddle.getBounds()).has_value()) {
        sf::FloatRect pBounds = paddle.getBounds();
        sf::FloatRect bBounds = ball.getBounds();

        // 1. Выталкиваем мяч чуть выше ракетки, чтобы он не застревал в текстуре
        ball.setPosition(bBounds.position.x, pBounds.position.y - BALL_RADIUS - 4.0f);

        // 2. ЕСЛИ МЯЧ ДОЛЖЕН ПРИЛИПНУТЬ:
        if (context.ballSticky) {
            context.isBallGlued = true;  // Включаем режим удержания
            context.ballSticky = false;  // Сбрасываем бонус, чтобы он сработал один раз

            // Вычисляем центр мяча по X и сохраняем отступ относительно левого края ракетки
            float ballCenter = bBounds.position.x + bBounds.size.x / 2.0f;
            context.stickyOffset = ballCenter - pBounds.position.x;

            return; // Выходим из функции, обычный отскок считать не нужно
        }


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

    }

