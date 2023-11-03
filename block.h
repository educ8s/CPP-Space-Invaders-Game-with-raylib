#pragma once
#include <raylib.h>

class Block 
{

public:
	Block(int x, int y);
	void Draw();
	Rectangle getRect();
	int x;
	int y;


private:


};