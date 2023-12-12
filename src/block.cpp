#include "block.h"

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::Draw() {
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255});
}

Rectangle Block::GetRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
