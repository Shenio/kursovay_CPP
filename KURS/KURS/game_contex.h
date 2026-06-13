#pragma once

struct GameContext {
    float& ballSpeed;         // Ссылка на текущую скорость шарика
    float& paddleWidth;       // Ссылка на текущую ширину каретки
    bool& ballSticky;         // Прилипает ли шарик к каретке
    bool& oneTimeBottom;      // Активно ли одноразовое дно
    int& playerScore;         // Очки игрока
    bool& triggerRandomTrajectory; // Флаг для бонуса 7 (изменение траектории)
};
