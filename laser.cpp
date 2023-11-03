#include "laser.h"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
	active = true;
	this -> position = position;
	this -> speed = speed;
}

void Laser::Draw()
{
	if(active)
		DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

void Laser::Update()
{
	if (active){
		if (position.y > GetScreenHeight() or position.y < 0) {
			active = false;
    
    		return;
  		}
	position.y += speed;
	}
}

Rectangle Laser::getRect()  {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}