#include "game.h"

Game::Game()
{
	spaceship = Spaceship();
	obstacles = CreateObstacles();
	aliens = CreateAliens();
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
}

void Game::Draw()
{
	spaceship.Draw();

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
