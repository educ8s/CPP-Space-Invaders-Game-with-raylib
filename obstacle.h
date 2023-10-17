#pragma once
#include <vector>

class Obstacle{

public:
	Obstacle(int x, int y);
	void Draw();
	int x;
	int y;
	std::vector<std::vector<int>> grid;

};