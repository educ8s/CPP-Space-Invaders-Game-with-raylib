#pragma once
#include <raylib.h>
#include <vector>
#include "laser.h"


class Spaceship {

public:
	Spaceship();
	~Spaceship();
	void Update();
	void Draw();
	void Reset();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	Rectangle GetRect();
	std::vector<Laser> lasers;

private:
    Texture2D image;
    Vector2 position;
	double lastFireTime;
	Sound laserSound;
};