#include "raylib.h"
#include <math.h>

int main()
{
    constexpr short screenWidth{800};
    constexpr short screenHeight{450};

    InitWindow(screenWidth, screenHeight, "Basic 2D Camera");

    SetTargetFPS(60);

    Rectangle player{
        0,  // Rectangle top-left corner position x
        0,  // Rectangle top-left corner position y
        50, // Rectangle width
        50, // Rectangle height
    };

    // (initial-position - (ground.width / 2)) + (player.width / 2)
    Rectangle ground{
        (0 - 100) + 25,
        0 + 50, //(initialPosition + (ground.height / 2))
        200,
        100,
    };

    Camera2D camera2d{
        {screenWidth / 2, screenHeight / 2}, // Camera Offset
        {player.x + 20, player.y + 20},      // Camera Target
        0,                                   // Camera Rotation
        1,                                   // Camera Zoom
    };

    constexpr float mouseScrollingSpeed{0.1f};

    constexpr float defaultZoom{1.0f};
    constexpr float minZoom{0.1f};
    constexpr float maxZoom{3.0f};

    constexpr float defaultRotation{0.0f};
    constexpr float minRotation{-22.5f};
    constexpr float maxRotation{22.5f};
    constexpr float rotationalSpeed{0.5f};

    constexpr float moveSpeed{5.0f};

    while (!WindowShouldClose())
    {
        // Camera zoom controls
        // Uses log scaling to provide consistent zoom speed
        camera2d.zoom = expf(logf(camera2d.zoom) + (GetMouseWheelMove() * mouseScrollingSpeed));

        // Limit the zooming
        if (camera2d.zoom > maxZoom)
            camera2d.zoom = maxZoom;
        else if (camera2d.zoom < minZoom)
            camera2d.zoom = minZoom;

        // Limit the rotation
        if (IsKeyDown(KEY_A) && camera2d.rotation > minRotation)
            camera2d.rotation -= rotationalSpeed;
        else if (IsKeyDown(KEY_S) && camera2d.rotation < maxRotation)
            camera2d.rotation += rotationalSpeed;

        // Reset the zoom and rotation to their defaults
        if (IsKeyPressed(KEY_R))
        {
            camera2d.rotation = defaultRotation;
            camera2d.zoom = defaultZoom;
        }

        // Move the camera's target and
        // reposition the player's x axis
        if (IsKeyDown(KEY_LEFT))
        {
            camera2d.target.x += -moveSpeed;
            player.x += -moveSpeed;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            camera2d.target.x += moveSpeed;
            player.x += moveSpeed;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera2d);

        DrawRectangleRec(ground, GRAY);
        DrawRectangleRec(player, RED);

        EndMode2D();

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
