#pragma once
#include "spaceship.h"
#include <vector>
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"

class Game{

    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int highscore;
        Music music;

    private:
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void AlienShootLaser();
        void DeleteInactiveLasers();
        void CheckForCollisions();
        void GameOver();
        void InitGame();
        void Reset();
        void CheckForHighscore();
        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();

        std::vector<Alien> aliens;
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Laser> alienLasers;
        MysteryShip mysteryShip;
        int aliensDirection;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeLastAlienLaserFired;
        float mysteryShipSpawnInterval;
	    float timeLastSpawn; 
        Sound explosionSound;
};