#include <block.h>

Block::Block(int x, int y){

	this -> x = x;
	this -> y = y;
}

void Block::Draw()
{
	DrawRectangle(x, y, 3, 3, Color{243, 216, 63, 255});
}
