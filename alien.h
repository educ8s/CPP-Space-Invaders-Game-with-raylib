#pragma once
#include <raylib.h>

class Alien{

public:
	Alien(int type, int x, int y);
	void Update();
	void Draw();
	int type;
	Texture2D image;
	Vector2 position;

};