#include "Player.hpp"


Player::Player(float startX, float startY) {
    position = {startX, startY};
    speed = 600.0f;
    size = 100;
    sprite_sheet_idle = LoadTexture("player_sprites/idle.png");  // Load after window is initialized
    sprite_sheet_run = LoadTexture("player_sprites/run.png"); 
    deltaTime = GetFrameTime();

    // Animation setup for 10 horizontal sprites (implemented directly)
    int anim_first = 0;
    int anim_last = 9;
    int anim_cur = 0;
    float anim_speed = 0.1f; // 0.1s per frame
    float anim_timer = anim_speed;
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

    if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) speed = 1000.0f;  // Sprint speed
    else speed = 600.0f;
    // Horizontal movement
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        position.x += speed * deltaTime;
        facing = 1;
    }
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        position.x -= speed * deltaTime;
        facing = -1;
    }

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
    Rectangle src = { frameWidth * anim_cur, 0, frameWidth, (float)sprite_sheet_idle.height };
    Rectangle dest = { position.x-(float)48*4, position.y-53*(4+2), (frameWidth)*4, ((float)sprite_sheet_idle.height)*4 };
    
    DrawTexturePro(sprite_sheet_idle, src, dest, {0,0}, 0.0f, WHITE);
}

void Player::draw_run_texture(){
    static int anim_first = 0;
    static int anim_last = 15;
    static int anim_cur = 0;
    static float anim_speed = 0.1f; // 0.1s per frame
    static float anim_timer = anim_speed;
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
