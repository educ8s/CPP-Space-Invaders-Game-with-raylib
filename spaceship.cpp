#include <raylib.h>
#include "spaceship.h"
#include <iostream>
#include "game.h"

Spaceship::Spaceship()
{	
    lastFireTime = 0.0;
  	image = LoadTexture("Graphics/spaceship.png");
  	position.x = (GetScreenWidth() - image.width) / 2.0f;
  	position.y = GetScreenHeight() - image.height - 100;
    laserSound = LoadSound("Sounds/laser.ogg");
}

void Spaceship::Draw()
{
  DrawTextureV(image, position, WHITE);
}

void Spaceship::Update()
{

  if (position.x >= GetScreenWidth() - image.width - 25)
  {
  	position.x = GetScreenWidth() - image.width -25;
  }else if (position.x < 25)
  {
  	position.x = 25;
  }

  for (auto it = lasers.begin(); it != lasers.end();) {
        if (!it->active) {
            it = lasers.erase(it);
        } else {
            ++it;
        }
    }
}  

Rectangle Spaceship::getRect()  {
    return { position.x, position.y, float(image.width), float(image.height) };
}

void Spaceship::Reset() {
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height;
    lasers.clear();
}

void Spaceship::MoveLeft() {
    // Implement logic to move the spaceship to the left...
    if (position.x > 25) {
        position.x -= 7.0f;
    }
}

void Spaceship::MoveRight() {
    // Implement logic to move the spaceship to the right...
    if (position.x < GetScreenWidth() - image.width - 25) {
        position.x += 7.0f;
    }
}

void Spaceship::FireLaser() {
     if (GetTime() - lastFireTime >= 0.35) {
        // Fire a laser
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));

        // Update the last fire time
        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

void Spaceship::Unload() {
    UnloadSound(laserSound);
}