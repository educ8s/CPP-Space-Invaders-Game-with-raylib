#include "game.h"

Game::Game()
{
	spaceship = Spaceship();
	obstacles = CreateObstacles();
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
}