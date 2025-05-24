#include "raylib.h"

int main()
{

    /*
   1. Initialise game objects
   2. Enter the main loop
   3. De-initialise game objects
    */

    constexpr short screenWidth{800};
    constexpr short screenHeight{450};

    InitWindow(screenWidth, screenHeight, "Input Mouse Wheel");

    SetTargetFPS(60);

    constexpr Vector2 boxSize{100, 100};
    Vector2 boxPosition{screenWidth / 2.0f, screenHeight / 2.0f};
    Color boxColor{RED};

    constexpr short scrollSpeed = 4; // Scrolling speed in pixels

    while (!WindowShouldClose())
    {

        boxPosition.y += GetMouseWheelMove() * scrollSpeed;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleV(boxPosition, boxSize, boxColor);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}