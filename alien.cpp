#include "alien.h"

Alien::Alien(int type, int x, int y)
{
	this -> type = type;
	position.x = x;
	position.y = y;
	alive = true;

	switch (type) {
		case 1:
			image = LoadTexture("Graphics/alien_1.png");
			break;
		case 2:
			image = LoadTexture("Graphics/alien_2.png");
			break;
		case 3:
			image = LoadTexture("Graphics/alien_3.png");
			break;
		default:
			image = LoadTexture("Graphics/alien_1.png");
			break;
	}
}

void Alien::Draw()
{
	if(alive)
		DrawTextureV(image, position, WHITE);
}

void Alien::Update(int direction)
{	
	position.x += direction;
}

Rectangle Alien::getRect()  {
    return { position.x, position.y, float(image.width), float(image.height) };
}