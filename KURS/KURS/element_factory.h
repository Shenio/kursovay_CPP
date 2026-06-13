#pragma once
#include "Base_element.h"
#include <memory>

class ElementFactory {
public:
    enum class Type {
        Standard,
        SizeBlock, // Наш блок скорости (из прошлых шагов)
        SizeBonus,
        BottomBonus,     // ТИП 6
        TrajectoryBonus  // ТИП 7
    };

    static std::unique_ptr<BaseElement> createElement(Type type, float x, float y);
};
