#pragma once
#include <raylib.h>

class Alien{

public:
	Alien(int type, int x, int y);
	void Update(int direction);
	void Draw();
	int type;
	bool alive;
	Texture2D image;
	Vector2 position;
	Rectangle getRect();
};