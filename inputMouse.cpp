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

    InitWindow(screenWidth, screenHeight, "Input Mouse");

    SetTargetFPS(60);

    Vector2 ballPosition{screenWidth / 2.0f, screenHeight / 2.0f};
    constexpr short ballRadius{50};
    Color currentBallColor{BLUE};

    while (!WindowShouldClose())
    {
        ballPosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            currentBallColor = RED;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            currentBallColor = BLUE;
        else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
            currentBallColor = PURPLE;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ballPosition, ballRadius, currentBallColor);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}