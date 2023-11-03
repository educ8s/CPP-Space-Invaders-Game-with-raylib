#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include <vector>
#include <list>
#include "alien.h"
#include "mystery_ship.h"
#include "laser.h"

class Game{

public:
	Game();
	void Update();
	void Draw();
	void AlienShootLaser();
	Spaceship spaceship;
	MysteryShip mystery_ship;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;
	std::vector<Laser> alienLasers;

private:
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
	void MoveAliens();
	int aliens_direction;
	void AliensMoveDown(int rows);
	void CheckForCollisions();
	void DeleteInactiveLasers();
	float mysteryShipSpawnInterval;
	float timeSinceLastSpawn;
	float alienLaserShootInterval;
    float timeSinceLastAlienLaser;

};