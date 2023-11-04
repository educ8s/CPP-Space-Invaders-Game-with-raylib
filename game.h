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
	~Game();
	void Update();
	void Draw();
	void AlienShootLaser();
	static void PlayLaserSound();
	Spaceship spaceship;
	MysteryShip mystery_ship;
	std::vector<Obstacle> obstacles;
	std::vector<Alien> aliens;
	std::vector<Laser> alienLasers;
	bool run;
	int lives;
	int score;
	int highscore;
	Music music;
    
private:
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> CreateAliens();
	void MoveAliens();
	int aliens_direction;
	void AliensMoveDown(int rows);
	void CheckForCollisions();
	void DeleteInactiveLasers();
	void InitGame();
	void GameOver();
	void Reset();
	void CheckForHighscore();
	void SaveHighscoreToFile(int highscore);
	int LoadHighscoreFromFile();  
	void HandleSpaceshipControls();
	float mysteryShipSpawnInterval;
	float timeSinceLastSpawn;
	float alienLaserShootInterval;
    float timeSinceLastAlienLaser;
    Sound explosionSound;
};