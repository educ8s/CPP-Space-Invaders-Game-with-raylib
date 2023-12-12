#include "mysteryship.h"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

void MysteryShip::Spawn() {

    alive = true;
    position.y = 90;

    int side = GetRandomValue(0, 1);

    if (side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - 25 - image.width;
        speed = -3;
    }
}

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

Rectangle MysteryShip::GetRect()
{
    if(alive) {
        return {position.x, position.y, float(image.width), float(image.height)};
    }else{
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Update()
{
	if(alive){
		position.x += speed;
		if(position.x > GetScreenWidth() - image.width - 25|| position.x < 25)
			alive = false;
	}
}

void MysteryShip::Draw() {
    if(alive)
        DrawTextureV(image, position, WHITE);
}