#include <raylib.h>
#include "spaceship.h"

Spaceship::Spaceship()
{	
  	position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

  // Load the spaceship image
  	image = LoadTexture("Graphics/spaceship.png");
  	  // Calculate the position of the spaceship sprite at the middle of the bottom of the screen
  	position.x = (GetScreenWidth() - image.width) / 2.0f;
  	position.y = GetScreenHeight() - image.height;
}

void Spaceship::Draw()
{
  DrawTextureV(image, position, WHITE);
}