#pragma once

// Было: 800 и 600
constexpr unsigned int WINDOW_WIDTH = 1024;
constexpr unsigned int WINDOW_HEIGHT = 768;

// Размеры элементов
constexpr float BLOCK_WIDTH = 60.0f;
constexpr float BLOCK_HEIGHT = 20.0f;
constexpr float BALL_RADIUS = 8.0f;
constexpr float PADDLE_HEIGHT = 15.0f;

// Начальные скорости и параметры физики
constexpr float INITIAL_BALL_SPEED = 0.1f;
constexpr float INITIAL_PADDLE_SPEED = 0.2f;
constexpr float BONUS_DROP_SPEED = 0.05f;

// Лимиты игрового процесса
constexpr int MAX_BLOCK_HEALTH = 5;
