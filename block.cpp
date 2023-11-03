#include <block.h>

Block::Block(int x, int y){

	this -> x = x;
	this -> y = y;
}

void Block::Draw()
{
	DrawRectangle(x, y, 3, 3, Color{243, 216, 63, 255});
}

Rectangle Block::getRect()  {
    Rectangle rect;
    rect.x = x;
    rect.y = y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
