#pragma once
#include "game_contex.h" // Нужен для структуры GameContext

// Опережающие объявления (Forward Declarations)
class Ball;
class Paddle;

class Cheak_contex {
public:
    static void Chek(GameContext& context, Ball& ball, Paddle& paddle);
};
