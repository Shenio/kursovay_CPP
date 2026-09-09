#pragma once
#include "base_block.h"
#include <memory>

class BlockFactory {
public:
    enum class Type {
        StandardBlock,
        SpeedBlock,
        unbr_block,
        hp_block

    };

    static std::unique_ptr<base_block> createElement(Type type, float x, float y,int hp);
};
