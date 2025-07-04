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

        static float s_originX{};

        if (IsKeyPressed(KEY_RIGHT))
            s_originX += tileW / 2.0f;
        else if (IsKeyPressed(KEY_LEFT))
            s_originX -= tileW / 2.0f;

        static float s_originY{};

        if (IsKeyPressed(KEY_UP))
            s_originY -= tileH / 2.0f;
        else if (IsKeyPressed(KEY_DOWN))
            s_originY += tileH / 2.0f;

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            s_originX = 0;
            s_originY = 0;
        }

        std::clog << "CURRENT X ORIGIN: " << s_originX << '\n';
        std::clog << "CURRENT Y ORIGIN: " << s_originY << '\n';

        DrawRectangleRec(refRec, LIGHTGRAY);

        DrawCircleV(Vector2{
                        redTile.x,
                        redTile.y,
                    },
                    4, BLUE);

        DrawCircleV(Vector2{
                        redTile.x + s_originX,
                        redTile.y + s_originY,
                    },
                    4, BLACK);

        DrawRectanglePro(
            redTile,
            Vector2{s_originX, s_originY},
            tileRotation,
            RED);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
