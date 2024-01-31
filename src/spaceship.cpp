#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 100;
    lastFireTime = 0.0;
    laserSound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
    position.x -= 7;
    if(position.x < 25) {
        position.x = 25;
    }
}

void Spaceship::MoveRight() {
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >= 0.35) {
        lasers.push_back(Laser({position.x + image.width/2 - 2,position.y},-6));
        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/ 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
