#include "laser.h"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
	active = true;
	this -> position = position;
	this -> speed = speed;
}

Laser::~Laser()
{
	std::cout << "Killed Laser" << std::endl;
}

void Laser::Draw()
{
	if(active)
		DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

void Laser::Update()
{
	if (active){
		if (position.y > GetScreenHeight()) {
			active = false;
    
    		return;
  		}
	position.y += speed;
	}
}