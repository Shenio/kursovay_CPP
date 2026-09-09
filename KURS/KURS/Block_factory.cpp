#include"Block_factory.h"
#include"SpeedBlock.h"
#include"StandartBlock.h"
#include"unbr_block.h"
#include"3hp_block.h"


std::unique_ptr<base_block> BlockFactory::createElement(Type type, float x, float y,int hp) {
    switch (type) {
    case Type::SpeedBlock:
        return std::make_unique<SpeedBlock>(x, y,1);
    case Type::StandardBlock:
        return std::make_unique<StandardBlock>(x, y, 1);
    case Type::unbr_block:
        return std::make_unique<unbr_block>(x, y, -1);
    case Type::hp_block:
        return std::make_unique<hp_block>(x, y, 3);
    default:
        return nullptr;
    }
}
