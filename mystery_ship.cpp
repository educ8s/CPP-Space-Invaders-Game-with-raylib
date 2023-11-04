#include "mystery_ship.h"

MysteryShip::MysteryShip()
{
	image = LoadTexture("Graphics/mystery.png");
}

void MysteryShip::Spawn()
{
	int side = GetRandomValue(0, 1);

    if (side == 0) {
        // Spawn on the left side
        position.x = 25;
        speed = 3;
    } else {
        // Spawn on the right side
        position.x = GetScreenWidth() - 25 - image.width;
        speed = -3;
    }
    position.y = 90;
    alive = true;
}

void MysteryShip::Draw()
{
	if(alive)
		DrawTextureV(image, position, WHITE);
}

void MysteryShip::Update()
{
	if(alive){
		position.x += speed;

		if(position.x > GetScreenWidth() - 25 - image.width || position.x < 25)
			alive = false;
	}
}

Rectangle MysteryShip::getRect()
{
	if(alive)
	 	return { position.x, position.y, float(image.width), float(image.height) };
	 else
	 	return { position.x, position.y, 0, 0 };
}