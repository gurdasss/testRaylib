#include <raylib.h>

int main()
{
    constexpr short screenW{800};
    constexpr short screenH{450};

    InitWindow(screenW, screenH, "PIXEL");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Intentionally not clearing the background

        DrawPixelV(GetMousePosition(), RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}