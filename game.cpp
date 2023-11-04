#include "game.h"
#include <iostream>
#include <fstream>

Game::Game()
{
	highscore = LoadHighscoreFromFile();
	mysteryShipSpawnInterval = GetRandomValue(10, 20);
    alienLaserShootInterval = 0.35;
    
    music = LoadMusicStream("Sounds/music.ogg");
    PlayMusicStream(music);
    explosionSound = LoadSound("Sounds/explosion.ogg");
    InitGame();
}

Game::~Game()
{
	spaceship.Unload();
    UnloadSound(explosionSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

void Game::InitGame()
{
	score = 0;
	spaceship = Spaceship();
	mystery_ship = MysteryShip();
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	timeSinceLastSpawn = 0.0f;
	timeSinceLastAlienLaser = 0.0f;
	aliens_direction = 1;
	lives = 3;
	run = true;
}

void Game::GameOver()
{
	run = false;
}

void Game::CheckForHighscore() {
	if(score > highscore) {
		highscore = score;
		SaveHighscoreToFile(highscore);
	}
}

void Game::HandleSpaceshipControls() {
    // Check for key presses to control the spaceship
    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    }
    
    if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLaser();
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
	int obstacles_width = 23 * 3;
	float gap = (GetScreenWidth() - (4 * obstacles_width))/5;
	for(int i=0; i < 4; i++)
	{
	 	int offset_x = (i + 1) * gap + i * obstacles_width;
	 	obstacles.push_back(Obstacle(offset_x, GetScreenHeight() - 200));
	}
	return obstacles;
}

void Game::Update()
{
	if(run){
		HandleSpaceshipControls();
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

	    if (timeSinceLastSpawn >= mysteryShipSpawnInterval)
	    {
	        mystery_ship.Spawn();
	        timeSinceLastSpawn = 0.0f;
	        mysteryShipSpawnInterval = GetRandomValue(10, 20);
	    }
	    DeleteInactiveLasers();
	}else
	{
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
    	}
  }
	
}

void Game::Reset() {
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
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
		
		if(alien.position.x + alien.image.width > GetScreenWidth() - 25)
		{
			aliens_direction = -1;
			AliensMoveDown(4);
		}
		if(alien.position.x < 25)
		{
			aliens_direction = 1;
			AliensMoveDown(4);
		}
		alien.Update(aliens_direction);
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
    
	//Spaceship
    for (Laser& laser : spaceship.lasers)
    {
    	//Check for collisions Spaceship Laser & Aliens
        auto it = aliens.begin(); // Iterator pointing to the beginning of the vector
        while (it != aliens.end()) // Loop while we haven't reached the end
        {
            if (CheckCollisionRecs(it->getRect(), laser.getRect()))
            {
            	if(it->type == 1)
            	{
            		score += 100;
            		
            	}else if(it -> type == 2)
            	{
            		score += 200;
            	}else if(it -> type == 3)
            	{
            		score += 300;
            	}
            	CheckForHighscore();
                it = aliens.erase(it); // Remove the alien
                laser.active = false;  // Deactivate the laser
                PlaySound(explosionSound);
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
            	score += 500;
            	CheckForHighscore();
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

        if(CheckCollisionRecs(alienLaser.getRect(), spaceship.getRect()))
        {
        	alienLaser.active = false;
        	lives --;
        	if(lives == 0){
        		GameOver();
        	}
        }
    }

    //Alien Collision with Obstacle
    for(auto& alien: aliens)
    {
    	for(auto& obstacle: obstacles)
        {
        	auto it = obstacle.blocks.begin();
        	while(it != obstacle.blocks.end())
        	{
        		if(CheckCollisionRecs(it->getRect(), alien.getRect()))
        		{
        			it = obstacle.blocks.erase(it);	
        		}else
        		{
        			it++;
        		}
        	}
        }
    }

    //Alien Collision with Spaceship
    for(auto& alien: aliens)
    {
    	if(CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
    	{
    		lives = 0;
    		GameOver();
    	}
    }

}

void Game::SaveHighscoreToFile(int highscore) {
    std::ofstream highscoreFile("highscore.txt");

    if (highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to save highscore to file." << std::endl;
    }
}

int Game::LoadHighscoreFromFile() {
    int loadedHighscore = 0;  // Default highscore in case of errors

    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }

    return loadedHighscore;
}