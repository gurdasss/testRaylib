#include <raylib.h>
#include <raymath.h>

int main()
{
    constexpr short screenW{800};
    constexpr short screenH{450};

    InitWindow(screenW, screenH, "Image");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    // Textures are loaded into VRAM (Video RAM)
    // GPU (Graphics Processing Unit) efficiently renders the loaded texture
    Texture2D raylibTexture{LoadTexture("assets/raylib_32x32.png")};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawTextureV(raylibTexture, Vector2{
        //                                 screenW / 2.0f - (raylibTexture.width / 2.0f),
        //                                 screenH / 2.0f - (raylibTexture.height / 2.0f),
        //                             },
        //              WHITE);

        DrawTextureEx(raylibTexture, GetMousePosition(),
                      0.0f, 5.0f, WHITE);

        EndDrawing();
    }

    // Unload the texture from VRAM
    UnloadTexture(raylibTexture);
    CloseWindow();

    return 0;
}