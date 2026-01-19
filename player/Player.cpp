#include "Player.hpp"


Player::Player(float startX, float startY) {
    position = {startX, startY};
    max_speed = 600.0f;
    acceleration = 2500.0f; // Increased for snappier control
    friction = 3200.0f;     // Higher friction for quick stop
    size = 100;
    sprite_sheet_idle = LoadTexture("player_sprites/idle.png");  // Load after window is initialized
    sprite_sheet_run = LoadTexture("player_sprites/run.png"); 
    deltaTime = GetFrameTime();
    velocityX = 0.0f;
    velocityY = 0.0f;
}


bool Player::is_idle(){
    // Check if any relevant key is pressed (movement or jump keys)
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ||
        IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ||
        IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) {
        return false; // Not idle, a key is pressed
    }
    return true; // Idle, no key is pressed
}


void Player::movement(int screenWidth, int screenHeight) {
    deltaTime = GetFrameTime();  // Update every frame!

    if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) max_speed = 1000.0f;  // Sprint speed
    else max_speed = 600.0f;

    // Horizontal movement input (acceleration)
    bool moving = false;
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        velocityX += acceleration * deltaTime;
        facing = 1;
        moving = true;
    }
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        velocityX -= acceleration * deltaTime;
        facing = -1;
        moving = true;
    }

    // Clamp velocityX to max speed
    if (velocityX > max_speed) velocityX = max_speed;
    if (velocityX < -max_speed) velocityX = -max_speed;

    // Apply friction when not moving and on ground
    if (!moving && onGround) {
        if (velocityX > 0) {
            velocityX -= friction * deltaTime;
            if (velocityX < 0) velocityX = 0;
        } else if (velocityX < 0) {
            velocityX += friction * deltaTime;
            if (velocityX > 0) velocityX = 0;
        }
    }

    // Update position.x with velocityX
    position.x += velocityX * deltaTime;

    // Jumping
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && onGround) {
        velocityY = -800.0f; // Jump impulse
        onGround = false;
    }

    // Apply gravity
    velocityY += gravity * deltaTime;
    position.y += velocityY * deltaTime;

    // Simple ground collision (bottom of screen)
    float groundY = screenHeight-5; // Adjust for sprite size/offset
    if (position.y >= groundY) {
        position.y = groundY;
        velocityY = 0.0f;
        onGround = true;
    }
}

void Player::draw_idle_texture() {
    // Animation logic (directly in Player)
    static int anim_first = 0;
    static int anim_last = 9;
    static int anim_cur = 0;
    static float anim_speed = 0.1f; // 0.1s per frame
    static float anim_timer = anim_speed;
    anim_timer -= deltaTime;
    if (anim_timer <= 0) {
        anim_cur++;
        if (anim_cur > anim_last) anim_cur = anim_first;
        anim_timer = anim_speed;
    }
    float frameWidth = (float)sprite_sheet_idle.width / 10.0f;
    Rectangle src;
    if (facing == 1) {
        // Facing right (normal)
        src = { frameWidth * anim_cur, 0, frameWidth, (float)sprite_sheet_idle.height };
    } else {
        // Facing left (flip horizontally)
        src = { frameWidth * (anim_cur + 1), 0, -frameWidth, (float)sprite_sheet_idle.height };
    }
    Rectangle dest = { position.x-(float)48*4, position.y-53*(4+2), (frameWidth)*4, ((float)sprite_sheet_idle.height)*4 };
    DrawTexturePro(sprite_sheet_idle, src, dest, {0,0}, 0.0f, WHITE);
}

void Player::draw_run_texture(){
    static int anim_first = 0;
    static int anim_last = 15;
    static int anim_cur = 0;
    float anim_speed = IsKeyDown(KEY_LEFT_SHIFT) ? 0.03f : 0.05f;
    static float anim_timer = 0.05f;
    anim_timer -= deltaTime;
    if (anim_timer <= 0) {
        anim_cur++;
        if (anim_cur > anim_last) anim_cur = anim_first;
        anim_timer = anim_speed;
    }
    float frameWidth = (float)sprite_sheet_run.width / 16.0f;
    Rectangle src;
    if (facing == 1) {
        src = { frameWidth * anim_cur, 0, frameWidth, (float)sprite_sheet_run.height };
    } else {
        src = { frameWidth * (anim_cur + 1), 0, -frameWidth, (float)sprite_sheet_run.height };
    }
    Rectangle dest = { position.x-(float)48*4, position.y-53*(4+2), (frameWidth)*4, ((float)sprite_sheet_run.height)*4 };
    DrawTexturePro(sprite_sheet_run, src, dest, {0,0}, 0.0f, WHITE); 
}

void Player::unload_texture(){
    UnloadTexture(sprite_sheet_idle);
}
