#include <raylib.h>
#include <raymath.h>
#include <iostream>

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "TEST");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    constexpr float tileW{20};
    constexpr float tileH{20};

    constexpr Rectangle refRec{
        (screenW / 2.0f) - 30,
        100 - 30,
        tileW * 2,
        tileH * 2,
    };

    constexpr Rectangle redTile{
        // add half of width and height
        // to set the tile to its true
        // center (relative to refRec)
        refRec.x + tileW,
        refRec.y + tileH,
        tileW,
        tileH,
    };

    Vector2 recPos{redTile.x, redTile.y};

    while (!WindowShouldClose())
    {

#if 0
        static int s_frameCounter{};
        constexpr int tileFPS{2};

        // update the tile's Y position
        // after (targetFPS / tileFPS) frame(s)
        if (++s_frameCounter >= (targetFPS / tileFPS))
        {
            // update the Y position of both the tile
            // and optionally of refRec
            refRec.y += tileH;
            redTile.y += tileH;

            s_frameCounter = 0;
        }

        // increase the frame counter's count
        // so that tile's Y position will
        // update much more quickly
        if (IsKeyDown(KEY_DOWN))
            s_frameCounter += 10;


        float directionY{};

        // change the Y direction of tile
        // to either left or right
        if (IsKeyPressed(KEY_RIGHT))
            directionY = 1;
        else if (IsKeyPressed(KEY_LEFT))
            directionY = -1;

        // change tile's X position based on user's input
        refRec.x += (tileW * directionY);
        redTile.x += (tileW * directionY);

#endif

        static float tileRotation{};

        // rotate the tile 90 degree around its pivot
        if (IsKeyPressed(KEY_UP))
        {
            if (tileRotation >= 360.0f)
                tileRotation = 0;

            float tileRotationRad{tileRotation * (PI / 180.0f)};
            std::clog << "Current Rotation in Degree: " << tileRotation << '\n';
            std::clog << "Current Rotation in Radians: "
                      << tileRotationRad << '\n';

            Vector2 rotatedPoint{Vector2Rotate(Vector2{-1, 0}, tileRotationRad)};

            recPos.x += rotatedPoint.x * tileW;
            recPos.y += rotatedPoint.y * tileH;

            printf("%.3fRad -> Vector2{%.3f, %.3f}\n",
                   tileRotationRad, rotatedPoint.x, rotatedPoint.y);

            tileRotation += 90;
        }

        if (CheckCollisionPointRec(GetMousePosition(),
                                   Rectangle{recPos.x, recPos.y, tileW, tileH}))
            std::clog << "Collision detected!!\n";

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(refRec, LIGHTGRAY);
        DrawCircleV(recPos, 2.5f, BLACK);

        DrawRectanglePro(
            redTile,
            Vector2{},
            tileRotation,
            RED);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
