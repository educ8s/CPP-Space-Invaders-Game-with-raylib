#pragma once
#include <raylib.h>

class MysteryShip {

public:
	MysteryShip();
	void Update();
	void Draw();
	void Spawn();
	Rectangle getRect();

	Vector2 position;
	Texture2D image;
	bool alive;
	int speed;
};