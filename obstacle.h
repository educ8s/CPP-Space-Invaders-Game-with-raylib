#pragma once
#include <vector>
#include "Block.h"

class Obstacle{

public:
	Obstacle(int x, int y);
	void Draw();
	int x;
	int y;
	std::vector<std::vector<int>> grid;
	std::vector<Block> blocks;

};