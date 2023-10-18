#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include <vector>

class Game{

public:
	Game();
	void Update();
	void Draw();
	Spaceship spaceship;
	std::vector<Obstacle> obstacles;

private:
	std::vector<Obstacle> CreateObstacles();
};