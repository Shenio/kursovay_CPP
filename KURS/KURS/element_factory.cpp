#include "element_factory.h"
#include "SizeBonus.h"
#include "BottomBonus.h"
#include "TrajectoryBonus.h"
#include "StickBonus.h"
#include"SpeedBonus.h"

std::unique_ptr<BaseElement> ElementFactory::createElement(Type type, float x, float y) {
    switch (type) {
    case Type::SizeBonus:
        return std::make_unique<SizeBonus>(x, y);
    case Type::BottomBonus:
        return std::make_unique<BottomBonus>(x, y);
    case Type::TrajectoryBonus:
        return std::make_unique<TrajectoryBonus>(x, y);
    case Type::SpeedBonus:
        return std::make_unique<SpeedBonus>(x, y);
    case Type::StickBonus:
        return std::make_unique<StickBonus>(x, y);
    default:
        return nullptr;
    }
}
