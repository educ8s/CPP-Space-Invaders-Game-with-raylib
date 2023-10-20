#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include <vector>
#include "alien.h"

class Game{

public:
	Game();
	void Update();
	void Draw();
	Spaceship spaceship;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;

private:
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
};