#pragma once
#include <raylib.h>

class Alien {

    public:
        Alien(int type, Vector2 position);
        void Update(int direction);
	    void Draw();
        int GetType();
        static void UnloadImages();
        Rectangle GetRect();
        Vector2 position;
        static Texture alienImages[3];
        int type;

    private:
        
};