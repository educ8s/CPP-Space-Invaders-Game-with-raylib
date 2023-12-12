#pragma once
#include <vector>
#include "Block.h"

class Obstacle{

    public:
        Obstacle(Vector2 position);
        void Draw();
        
        static std::vector<std::vector<int>> grid;
	    std::vector<Block> blocks;

    private:
        Vector2 position;
};