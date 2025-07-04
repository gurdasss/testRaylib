#include <raylib.h>
#include <iostream>

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "TEST");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        static float tileRotation{};

        if (IsKeyPressed(KEY_SPACE))
        {
            if (tileRotation >= 360.0f)
                tileRotation = 0;

            tileRotation += 90;

            std::clog << "Current Rotation: " << tileRotation << '\n';
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        constexpr float tileW{20};
        constexpr float tileH{20};

        constexpr Rectangle refRec{
            (screenW / 2.0f) - 30,
            (screenH / 2.0f) - 30,
            tileW * 3,
            tileH * 3,
        };

        constexpr Rectangle redTile{
            screenW / 2.0f,
            screenH / 2.0f,
            tileW,
            tileH,
        };

        DrawRectangleRec(refRec, LIGHTGRAY);

        DrawRectanglePro(
            redTile,
            Vector2{-tileW / 2.0f, -tileH / 2.0f},
            tileRotation,
            RED);

        DrawRectanglePro(
            redTile,
            Vector2{tileW / 2.0f, -tileH / 2.0f},
            tileRotation,
            RED);

        DrawRectanglePro(
            redTile,
            Vector2{tileW + (tileW / 2.0f), -tileH / 2.0f},
            tileRotation,
            RED);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
