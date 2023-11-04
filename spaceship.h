#pragma once
#include <vector>
#include "laser.h"

class Spaceship {

public:
	Spaceship();

	void Update();
	void Draw();
	void Reset();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	void Unload();
	Rectangle getRect();

	std::vector<Laser> lasers;
	Vector2 position;
	Texture2D image;

private:
	double lastFireTime;
	Sound laserSound;
};