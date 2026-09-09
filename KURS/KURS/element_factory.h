#pragma once
#include "Base_element.h"
#include <memory>

class ElementFactory {
public:
    enum class Type {
        SizeBonus,
        BottomBonus,     // ТИП 6
        TrajectoryBonus,  // ТИП 7
        SpeedBonus,
        StickBonus

    };

    static std::unique_ptr<BaseElement> createElement(Type type, float x, float y);
};
