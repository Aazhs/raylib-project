#include "raylib.h"
#include "player/Player.hpp"

int main() {
    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 900;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "bing");
    ToggleFullscreen();

    //ToggleFullscreen();
    SetTargetFPS(144);

    Player player(SCREEN_WIDTH / 2, 0);
    Texture2D background = LoadTexture("image.png");

    while (!WindowShouldClose()) {   
        player.movement(SCREEN_WIDTH, SCREEN_HEIGHT);
        bool idle = player.is_idle();

        BeginDrawing();

            // Stretch background to fit screen
            DrawTexturePro(
                background,
                (Rectangle){0, 0, (float)background.width, (float)background.height},
                (Rectangle){0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
                (Vector2){0, 0},
                0.0f,
                WHITE
            );

            //debug info
            DrawFPS(10,10);
            DrawText(TextFormat("( %.2f , %.2f )", player.position.x, player.position.y), 100, 9, 20, LIME);   // Show player position at top left
            

            //player draw
            if(idle == 1) player.draw_idle_texture();          //idle
            else player.draw_run_texture();                 //non idle

        EndDrawing();
    }

    player.unload_texture(); //memory unloaded
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
