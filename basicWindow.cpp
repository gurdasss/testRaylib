#include "raylib.h"

int main()
{
    constexpr int windowWidth{500};
    constexpr int windowHeight{400};
    const char *title{"MY FIRST RAYLIB PROJECT"};

    InitWindow(windowWidth, windowHeight, title);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("HELLO RAYLIB!!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}