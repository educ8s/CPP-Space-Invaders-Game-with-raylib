#pragma once
#include <vector>
#include "laser.h"

class Spaceship {

public:
	Spaceship();

	void Update();
	void Draw();

	std::vector<Laser> lasers;
	Vector2 position;
	Texture2D image;

private:
	double lastFireTime;
};