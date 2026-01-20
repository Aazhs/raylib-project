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

    // Camera target for lerp
    Vector2 cameraTarget = player.position;
    const float cameraLerp = 0.1f; // Adjust for smoothness (0.0f - 1.0f)

    while (!WindowShouldClose()) {
        player.movement(SCREEN_WIDTH, SCREEN_HEIGHT);
        bool idle = player.is_idle();

        // Lerp camera target towards player
        cameraTarget.x += (player.position.x - cameraTarget.x) * cameraLerp;
        cameraTarget.y += (player.position.y - cameraTarget.y) * cameraLerp;

        // Camera initialise
        Camera2D camera = {0};
        camera.target = cameraTarget;
        camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT };
        camera.rotation = 0.0f;
        camera.zoom = 1.2f;

        BeginDrawing();
            BeginMode2D(camera);

            // Stretch background to fit screen
            ClearBackground(BLACK);
            DrawTexturePro(
                background,
                (Rectangle){0, 0, (float)background.width, (float)background.height},
                (Rectangle){-SCREEN_WIDTH, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
            DrawTexturePro(
                background,
                (Rectangle){0, 0, (float)background.width, (float)background.height},
                (Rectangle){0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
            DrawTexturePro(
                background,
                (Rectangle){0, 0, (float)background.width, (float)background.height},
                (Rectangle){SCREEN_WIDTH, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
                (Vector2){0, 0},
                0.0f,
                WHITE
            );

            //player draw
            if(idle == 1) player.draw_idle_texture();          //idle
            else player.draw_run_texture();                 //non idle

        EndMode2D();
        //debug info (world space)

        DrawFPS(10, 10);
        DrawText(TextFormat("( %.2f , %.2f )", player.position.x, player.position.y), 100, 9, 20, LIME);   // Show player position at top left

    EndDrawing();
    }

    player.unload_texture(); //memory unloaded
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
