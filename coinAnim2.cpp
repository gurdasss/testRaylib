#include <raylib.h>
#include <cassert> // for assert()

void textureScaling(Texture2D &texture, int scale, const char *textureFilePath);

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "Animation 2");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Texture2D coinSSTexture{};

    // search for the file relative to current working directory (coinAnim2.cpp)
    textureScaling(coinSSTexture, 5, "assets/coin.png");

    constexpr int noAnimFrames{12};

    Rectangle textureRegion{
        0,
        0,
        static_cast<float>(coinSSTexture.width) / noAnimFrames,
        static_cast<float>(coinSSTexture.height),
    };

    Vector2 textureDrawingPos{
        screenW / 2 - (textureRegion.width / 2),
        screenH / 2 - (textureRegion.height / 2),
    };

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    constexpr int animFPS{10};

    while (!WindowShouldClose())
    {
        static int s_frameCounter{};
        static int s_coinCurrentFrame{};

        if (s_frameCounter == (targetFPS / animFPS))
        {
            // Update texture region position

            // clamp coin current animation frame
            s_coinCurrentFrame = s_coinCurrentFrame % noAnimFrames;

            // update texture region's position
            textureRegion.x = textureRegion.width *
                              static_cast<float>(s_coinCurrentFrame);
            textureRegion.y = 0;

            ++s_coinCurrentFrame;
            // reset frame counter
            s_frameCounter = 0;
        }

        ++s_frameCounter;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureRec(coinSSTexture, textureRegion, textureDrawingPos, WHITE);

        EndDrawing();
    }

    UnloadTexture(coinSSTexture);

    CloseWindow();
    return 0;
}

void textureScaling(Texture2D &texture, int scale, const char *textureFilePath)
{

    if (FileExists(textureFilePath))
    {
        // first load the texture as an image in RAM
        // to perform image processing by CPU
        Image textureImage{LoadImage(textureFilePath)};

        // Resize image using (Nearest-Neighbor scaling algorithm)
        // to avoid any pixel blur
        ImageResizeNN(&textureImage,
                      textureImage.width * scale,
                      textureImage.height * scale);

        // reload the newly scaled image as texture in VRAM
        texture = LoadTextureFromImage(textureImage);

        // we are done with the image
        UnloadImage(textureImage);
    }
    else
        assert(false && "Texture file do not exist");
}