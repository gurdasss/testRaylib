#include <raylib.h>
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

    Rectangle refRec{
        (screenW / 2.0f) - 30,
        100 - 30,
        tileW * 3,
        tileH * 3,
    };

    Rectangle redTile{
        // add half of width and height
        // to set the tile to its true
        // center (relative to refRec)
        refRec.x + (refRec.width / 2.0f),
        refRec.y + (refRec.height / 2.0f),
        tileW,
        tileH,
    };

    while (!WindowShouldClose())
    {
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

        static float tileRotation{};

        // rotate the tile 90 degree around its pivot
        if (IsKeyPressed(KEY_UP))
        {
            if (tileRotation >= 360.0f)
                tileRotation = 0;

            tileRotation += 90;

            std::clog << "Current Rotation: " << tileRotation << '\n';
        }

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

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(refRec, LIGHTGRAY);

        DrawRectanglePro(
            redTile,
            // set the pivot to half left side and
            // half upward
            Vector2{-tileW / 2.0f, -tileH / 2.0f},
            tileRotation,
            RED);

        DrawRectanglePro(
            redTile,
            // set the pivot to half right side and
            // half upward
            Vector2{tileW / 2.0f, -tileH / 2.0},
            tileRotation,
            RED);

        DrawRectanglePro(
            redTile,
            // set the pivot to top-right + half right side and
            // half upward
            Vector2{tileW + (tileW / 2.0f), -tileW / 2.0},
            tileRotation,
            RED);

        DrawRectanglePro(
            redTile,
            // set the pivot to half right side and
            // half downward
            Vector2{tileW / 2.0f, tileW / 2.0},
            tileRotation,
            RED);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
