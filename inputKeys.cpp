#include "raylib.h"

int main()
{
    /*
     1. Initialise game objects
     2. Enter the main loop
     3. De-initialise game objects
    */

    // 1. Initialise game objects

    constexpr short screenWidth{800};
    constexpr short screenHeight{450};

    InitWindow(screenWidth, screenHeight, "Keyboard Input");

    // setting the desired FPS
    SetTargetFPS(60);

    // setting the initial position of the ball
    Vector2 ballPosition{screenWidth / 2.0f, screenHeight / 2.0f};
    constexpr short ballRadius{20};

    constexpr short steps{2};

    // Detect window close button or ESC key
    while (!WindowShouldClose())
    {
        // 2. Enter the main loop

        // Update game objects

        // Update the ball position based on user's input
        if (IsKeyDown(KEY_RIGHT))
            ballPosition.x += steps;
        if (IsKeyDown(KEY_LEFT))
            ballPosition.x -= steps;

        if (IsKeyDown(KEY_UP))
            ballPosition.y -= steps;
        if (IsKeyDown(KEY_DOWN))
            ballPosition.y += steps;

        // Render everything
        BeginDrawing();

        // Clear the previous frame
        ClearBackground(RAYWHITE);

        DrawCircleV(ballPosition, ballRadius, RED);

        // Draw the FPS at 0, 0 position
        DrawFPS(0, 0);

        EndDrawing();
    }

    // 3. De-initialise game objects

    CloseWindow();

    return 0;
}