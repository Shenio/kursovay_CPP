#include <SFML/Graphics.hpp>
#include "constant.h"
#include "game_contex.h"
#include "GameField.h"
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include "Cheak_contex.h" 


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
    bool isBallGlued = false;
    // ОБЯЗАТЕЛЬНО ДОБАВИТЬ ТУТ:
    bool isGameStarted = false;
    float stickyOffset = 0;

    // Создаем контекст
    GameContext context{
        currentBallSpeed,
        currentPaddleWidth,
        ballSticky,
        oneTimeBottom,
        score,
        triggerTrajectory,
        isGameStarted,
        isBallGlued,
        stickyOffset

    };


    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        paddle.update(static_cast<float>(WINDOW_WIDTH));
        if (!context.isGameStarted || context.isBallGlued) {
            sf::FloatRect pBounds = paddle.getBounds();

            if (!context.isGameStarted) {
                // Логика до старта: держим мяч строго по центру
                ball = Ball(pBounds.position.x + pBounds.size.x / 2.0f, pBounds.position.y - BALL_RADIUS - 4.0f);
            }
            else if (context.isBallGlued) {
                // Логика прилипания во время игры: плавно двигаем за ракеткой
                ball.setPosition(pBounds.position.x + context.stickyOffset, pBounds.position.y - BALL_RADIUS - 4.0f);
            }

            // Логика запуска по кнопке Space
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                if (!context.isGameStarted) {
                    context.isGameStarted = true;
                    float randomAngle = -(3.14159f / 4.0f + (rand() % 100 / 100.0f) * (3.14159f / 2.0f));
                    ball.setRandomAngle(randomAngle);

                }
                else if (context.isBallGlued) {
                    context.isBallGlued = false; // Отлепляем мяч

                    float randomAngle = -(3.14159f / 4.0f + (rand() % 100 / 100.0f) * (3.14159f / 2.0f));
                    ball.setRandomAngle(randomAngle);
                }
            }
        }

        else {

            Cheak_contex::Chek(context, ball, paddle);

        }


        field.update();


        sf::FloatRect ballBounds = ball.getBounds();
        field.checkCollisions_ball(ball,ballBounds,context);

        sf::FloatRect paddleBounds = paddle.getBounds();
        field.checkCollisions_padel(paddleBounds, context);

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
