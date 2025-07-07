#include <raylib.h>
#include <raymath.h>
#include <iostream>

void rotateRec(const Vector2 &orientation, Vector2 &recPos, float radian);

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "TEST");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    constexpr float tileW{20};
    constexpr float tileH{20};

    Rectangle refRec{
        (screenW / 2.0f) - 30,
        100 - 30,
        tileW * 2,
        tileH * 2,
    };

    // only the position needs to be updated
    // and setting initial position relative to reference rectangle
    Vector2 recPos1{refRec.x + tileW, refRec.y + tileH};
    Vector2 recPos2{refRec.x, refRec.y + tileH};

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
            recPos1.y += tileH;
            recPos2.y += tileH;

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
        recPos1.x += (tileW * directionY);
        recPos2.x += (tileW * directionY);

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

            // {-1, 0} for recPos1
            // {0, -1} for recPos2

            // rotate each Vector2 position based on the
            // respective orientation and rotation in radian
            rotateRec(Vector2{-1, 0}, recPos1, tileRotationRad);
            rotateRec(Vector2{0, -1}, recPos2, tileRotationRad);

            // printf("%.3fRad -> Vector2{%.3f, %.3f}\n",
            //        tileRotationRad, rotatedPoint.x, rotatedPoint.y);

            tileRotation += 90;
        }

        if (CheckCollisionPointRec(GetMousePosition(),
                                   Rectangle{recPos1.x, recPos1.y, tileW, tileH}))
            std::clog << "Collision detected!!\n";

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(refRec, LIGHTGRAY);
        DrawCircleV(recPos1, 2.5f, BLACK);
        DrawCircleV(recPos2, 2.5f, BLACK);

        DrawRectangle(recPos1.x, recPos1.y, tileW, tileH, RED);
        DrawRectangle(recPos2.x, recPos2.y, tileW, tileH, RED);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void rotateRec(const Vector2 &orientation, Vector2 &recPos, float radian)
{
    constexpr float tileW{20};
    constexpr float tileH{20};

    Vector2 rotatedPoint{Vector2Rotate(orientation, radian)};

    recPos.x += rotatedPoint.x * tileW;
    recPos.y += rotatedPoint.y * tileH;
}