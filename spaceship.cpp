#include <raylib.h>
#include "spaceship.h"
#include <iostream>

Spaceship::Spaceship()
{	
  	image = LoadTexture("Graphics/spaceship.png");
  	position.x = (GetScreenWidth() - image.width) / 2.0f;
  	position.y = GetScreenHeight() - image.height;
}

void Spaceship::Draw()
{
  DrawTextureV(image, position, WHITE);
}

void Spaceship::Update()
{
	if (IsKeyDown(KEY_LEFT)) {
    position.x -= 7.0f;
  } else if (IsKeyDown(KEY_RIGHT)) {
    position.x += 7.0f;
  }else if(IsKeyDown(KEY_SPACE))
  {
    lasers.push_back(Laser({position.x + image.width/2 - 2, position.y}, -6));
  }

  if (position.x >= GetScreenWidth() - image.width)
  {
  	position.x = GetScreenWidth() - image.width;
  }else if (position.x < 0)
  {
  	position.x = 0;
  }

  for (auto it = lasers.begin(); it != lasers.end();) {
        if (!it->active) {
            it = lasers.erase(it);
        } else {
            ++it;
        }
    }
}  