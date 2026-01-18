#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "raylib.h"



class Player {
public:
    Player(float startX, float startY);
    Vector2 position;  // Screen coordinates
    float speed;
    int size;
    float deltaTime;
    Texture2D sprite_sheet_idle;
    Texture2D sprite_sheet_run;

    float velocityY = 0.0f;
    float gravity = 2000.0f;
    bool onGround = false;

    int facing = 1; // 1 = right, -1 = left

    void movement(int screenWidth, int screenHeight);

    void draw_idle_texture();
    void draw_run_texture();
    void unload_texture();
    bool is_idle();
};

#endif
