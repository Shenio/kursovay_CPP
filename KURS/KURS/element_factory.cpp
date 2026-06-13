#include "element_factory.h"
#include "StandartBlock.h"
#include "SizeBlock.h"
#include "SizeBonus.h"
#include "BottomBonus.h"
#include "TrajectoryBonus.h"

std::unique_ptr<BaseElement> ElementFactory::createElement(Type type, float x, float y) {
    switch (type) {
    case Type::Standard:
        return std::make_unique<StandardBlock>(x, y, 1);
    case Type::SizeBlock:
        return std::make_unique<SizeBlock>(x, y);
    case Type::SizeBonus:
        return std::make_unique<SizeBonus>(x, y);
    case Type::BottomBonus:
        return std::make_unique<BottomBonus>(x, y);
    case Type::TrajectoryBonus:
        return std::make_unique<TrajectoryBonus>(x, y);
    default:
        return nullptr;
    }
}
