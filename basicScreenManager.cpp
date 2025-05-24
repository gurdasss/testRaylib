#include "raylib.h"

namespace ScreenManager
{
    enum GameScreen
    {
        LOGO,
        TITLE,
        GAMEPLAY,
        ENDING
    };
} // namespace ScreenManager

void updateCurrentScreen(ScreenManager::GameScreen &currentScreen);
void drawCurrentScreen(const ScreenManager::GameScreen &currentScreen);

constexpr short screenWidth{800};
constexpr short screenHeight{450};

int main()
{

    ScreenManager::GameScreen currentScreen{ScreenManager::LOGO};

    InitWindow(screenWidth, screenHeight, "My screen manager");

    // setting the desired FPS
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // UPDATE CURRENT SCREEN BASED ON USER'S INPUT
        updateCurrentScreen(currentScreen);

        BeginDrawing();

        ClearBackground(BLACK);

        // DRAW ALL YOUR STUFF HERE!!

        // DRAW CURRENT SCREEN
        drawCurrentScreen(currentScreen);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void updateCurrentScreen(ScreenManager::GameScreen &currentScreen)
{
    static short frameCounter{};

    switch (currentScreen)
    {
    case ScreenManager::LOGO:
        ++frameCounter;

        if (frameCounter > 120)
            currentScreen = ScreenManager::TITLE;
        break;

    case ScreenManager::TITLE:

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            currentScreen = ScreenManager::GAMEPLAY;

        break;

    case ScreenManager::GAMEPLAY:

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            currentScreen = ScreenManager::ENDING;

        break;

    case ScreenManager::ENDING:

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            currentScreen = ScreenManager::TITLE;

        break;

    default:
        break;
    }
}
void drawCurrentScreen(const ScreenManager::GameScreen &currentScreen)
{
    switch (currentScreen)
    {
    case ScreenManager::LOGO:

        // TODO: Draw LOGO screen here!
        DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
        DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

        break;

    case ScreenManager::TITLE:

        // TODO: Draw TITLE screen here!
        DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
        DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
        DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

        break;

    case ScreenManager::GAMEPLAY:

        // TODO: Draw GAMEPLAY screen here!
        DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
        DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
        DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

        break;

    case ScreenManager::ENDING:

        // TODO: Draw ENDING screen here!
        DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
        DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
        DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

        break;

    default:
        break;
    }
}