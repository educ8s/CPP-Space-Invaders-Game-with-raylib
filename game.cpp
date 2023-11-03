#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game()
{
	spaceship = Spaceship();
	mystery_ship = MysteryShip();
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliens_direction = 1;
	mysteryShipSpawnInterval = GetRandomValue(10, 20);
    timeSinceLastSpawn = 0.0f;
    alienLaserShootInterval = 0.35;
    timeSinceLastAlienLaser = 0.0f;
}

std::vector<Obstacle> Game::CreateObstacles()
{
	int obstacles_width = 23 * 3;
	float gap = (GetScreenWidth() - (4 * obstacles_width))/5;
	for(int i=0; i < 4; i++)
	{
	 	int offset_x = (i + 1) * gap + i * obstacles_width;
	 	obstacles.push_back(Obstacle(offset_x, GetScreenHeight() - 100));
	}
	return obstacles;
}

void Game::Update()
{
	spaceship.Update();
    for(Laser& laser: spaceship.lasers){
        laser.Update();
    }

    for(Laser& alienLaser: alienLasers)
    	alienLaser.Update();

    MoveAliens();
    AlienShootLaser();
    mystery_ship.Update();
    CheckForCollisions();

    timeSinceLastSpawn += GetFrameTime();

    // Check if it's time to spawn the MysteryShip
    if (timeSinceLastSpawn >= mysteryShipSpawnInterval)
    {
        mystery_ship.Spawn();
        timeSinceLastSpawn = 0.0f;
        // Set a new random spawn interval
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
    }
    DeleteInactiveLasers();

    std::cout << "Alien Lasers:" << alienLasers.size() << std::endl;
}

void Game::Draw()
{
	spaceship.Draw();
	mystery_ship.Draw();

    for(Obstacle& obstacle: obstacles)
    {
        obstacle.Draw();
    }

    for(Laser& laser: spaceship.lasers){
        laser.Draw();
    }

    for(Alien& alien: aliens)
    {
    	alien.Draw();
    }

    for(Laser& alien_laser: alienLasers)
    {
    	alien_laser.Draw();
    }
}

std::vector<Alien> Game::CreateAliens()
{
	for (int row = 0; row < 5; row++) {
			for (int column = 0; column < 11; column++) {
				int x = 75 + column * 55;
				int y = 110 + row * 55;

				int alien_type;
				if (row == 0) {
					alien_type = 3;
				} else if (row == 1 || row == 2) {
					alien_type = 2;
				} else {
					alien_type = 1;
				}

				Alien alien = Alien(alien_type, x, y);
				aliens.push_back(alien);
			}
		}

		return aliens;
}

void Game::MoveAliens()
{
	for(Alien& alien: aliens)
	{
		alien.Update(aliens_direction);
		if(alien.position.x + alien.image.width > GetScreenWidth())
		{
			aliens_direction = -1;
			AliensMoveDown(4);
		}
		if(alien.position.x < 0)
		{
			aliens_direction = 1;
			AliensMoveDown(4);
		}
	}

}

void Game::AliensMoveDown(int rows)
{
	for(Alien& alien: aliens)
	{
		alien.position.y += rows;
	}
}


void Game::AlienShootLaser()
{
	 // Get the current time in seconds
    double currentTime = GetTime();

    // Check if enough time has passed (alienLaserShootInterval) since the last shot
    if (currentTime - timeSinceLastAlienLaser >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& randomAlien = aliens[randomIndex];
        alienLasers.push_back(Laser({randomAlien.position.x + randomAlien.image.width/2 , randomAlien.position.y + randomAlien.image.height}, 6));

        // Update the last shoot time
        timeSinceLastAlienLaser = currentTime;
    }
}

void Game::DeleteInactiveLasers()
{
	auto it = alienLasers.begin();
	while(it != alienLasers.end())
	{
		if(it-> active == false)
		{
			it = alienLasers.erase(it);
		}else
		{
			it++;
		}
	}
}

void Game::CheckForCollisions()
{
    for (Laser& laser : spaceship.lasers)
    {
    	//Check for collisions Spaceship Laser & Aliens
        auto it = aliens.begin(); // Iterator pointing to the beginning of the vector
        while (it != aliens.end()) // Loop while we haven't reached the end
        {
            if (CheckCollisionRecs(it->getRect(), laser.getRect()))
            {
                it = aliens.erase(it); // Remove the alien
                laser.active = false;  // Deactivate the laser
            }
            else
            {
                it++; // Move to the next alien
            }
        }

        //Check for collision with obstacles
        for(auto& obstacle: obstacles)
        {
        	auto it = obstacle.blocks.begin();
        	while(it != obstacle.blocks.end())
        	{
        		if(CheckCollisionRecs(it->getRect(), laser.getRect()))
        		{
        			it = obstacle.blocks.erase(it);
        			laser.active = false;
        		}else
        		{
        			it++;
        		}
        	}
        }

        if (CheckCollisionRecs(mystery_ship.getRect(), laser.getRect()))
            {
                mystery_ship.alive = false;
                laser.active = false;
            }
    }

    //Alien Lasers
    for(Laser& alienLaser: alienLasers)
    {
    	for(auto& obstacle: obstacles)
        {
        	auto it = obstacle.blocks.begin();
        	while(it != obstacle.blocks.end())
        	{
        		if(CheckCollisionRecs(it->getRect(), alienLaser.getRect()))
        		{
        			it = obstacle.blocks.erase(it);
        			alienLaser.active = false;
        		}else
        		{
        			it++;
        		}
        	}
        }
    }

}