#include "Rectangle2D.h"
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

    Rectangle2D refRec{tileW * 2, tileH * 2};
    refRec.setTint(LIGHTGRAY);
    refRec.setPosition(Vector2{(screenW / 2.0f) - 20, 100});

    Rectangle2D tile{tileW, tileH};
    tile.setTint(RED);
    tile.setPosition(Vector2{refRec.getX() + tileW, refRec.getY() + tileH});

    Rectangle2D tile2{tileW, tileH};
    tile2.setTint(BLUE);
    tile2.setPosition(Vector2{tile.getX() + tileW, tile.getY() - tileH});

    while (!WindowShouldClose())
    {
        static int s_frameCounter{};
        constexpr int tileFPS{2};

        static float tileRotation{};

        // update the tile's Y position
        // after (targetFPS / tileFPS) frame(s)
        if (++s_frameCounter >= (targetFPS / tileFPS))
        {

            // tile.setY(tile.getY() + tile.getHeight());
            // tile2.setY(tile2.getY() + tile2.getHeight());

            s_frameCounter = 0;
        }

        // increase the frame counter's count
        // so that tile's Y position will
        // update much more quickly
        if (IsKeyDown(KEY_DOWN))
            s_frameCounter += 10;

        // TODO: Somehow need to rotate two-tiles clockwise
        // based on user's input
        if (IsKeyPressed(KEY_UP))
        {
            if (tileRotation >= 360.0f)
                tileRotation = 0;

            tileRotation += 90;

            std::clog << "Current Rotation: " << tileRotation << '\n';
        }

#if 0
        float directionY{};

        // change the Y direction of tile
        // to either left or right
        if (IsKeyPressed(KEY_RIGHT))
            directionY = 1;
        else if (IsKeyPressed(KEY_LEFT))
            directionY = -1;

        // change tile's X position based on user's input
        tile.setX(tile.getX() + (tile.getWidth() * directionY));
        tile2.setX(tile2.getX() + (tile2.getWidth() * directionY));
#endif

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(refRec.getRectangle(), refRec.getTint());
        // DrawRectangleRec(tile.getRectangle(), tile.getTint());
        // DrawRectanglePro(
        //     tile.getRectangle(),
        //     Vector2{},
        //     tileRotation,
        //     tile.getTint());

        DrawRectanglePro(
            Rectangle{
                refRec.getX() + tileW,
                refRec.getY() + tileH,
                -tileW,
                -tileH},
            Vector2{-tileW, 0.0f},
            tileRotation,
            tile2.getTint());

        // DrawRectangleRec(tile2.getRectangle(), tile2.getTint());

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
