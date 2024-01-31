#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Laser::Draw() {
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update() {
    position.y += speed;
    if(active) {
        if(position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false;
        }
    }
}