#include <raylib.h>

int main()
{
    constexpr short screenW{800};
    constexpr short screenH{450};

    InitWindow(screenW, screenH, "Animation");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    // Textures are loaded into VRAM (Video RAM)
    // GPU (Graphics Processing Unit) efficiently renders the loaded texture
    Texture2D coinSpriteSheet{};
    Rectangle spriteFrame{};
    constexpr short noOfFrames{12};

    // Making an explicit block scope
    // to restrict the use of Image
    {
        // Images are loaded into RAM
        // CPU (Central Processing Unit) handles the loaded image
        Image coinSpriteSheetImage{LoadImage("assets/coin.png")};

        constexpr short scale{5};

        // Resize image using (Nearest-Neighbor scaling algorithm)
        // keep the aspect ratio same
        ImageResizeNN(&coinSpriteSheetImage, coinSpriteSheetImage.width * scale,
                      coinSpriteSheetImage.height * scale);

        // Convert the newly resized Image into a Texture
        coinSpriteSheet = LoadTextureFromImage(coinSpriteSheetImage);

        spriteFrame.x = 0;
        spriteFrame.y = 0;

        // Set the width and height of a single frame
        spriteFrame.width = static_cast<float>(coinSpriteSheetImage.width / noOfFrames);
        spriteFrame.height = static_cast<float>(coinSpriteSheetImage.height);

        // Unload the Image from RAM
        // We will use texture from now on!
        UnloadImage(coinSpriteSheetImage);
    }

    // Draw the animation in the middle of the screen
    Vector2 spriteDrawingPos{
        screenW / 2.0f - (spriteFrame.width / 2.0f),
        screenH / 2.0f - (spriteFrame.height / 2.0f)};

    constexpr short animFPS{8};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        static short s_frameCounter{};
        static short currentFrame{};

        if (++s_frameCounter == animFPS)
        {
            // clamp the current frame value
            // based on noOfFrames
            currentFrame = currentFrame % noOfFrames;

            spriteFrame.x = currentFrame * spriteFrame.width;

            // rest the frame counter
            s_frameCounter = 0;
            ++currentFrame;
        }

        DrawTextureRec(coinSpriteSheet, spriteFrame, spriteDrawingPos, WHITE);
        // DrawTextureV(coinSpriteSheet, Vector2{0, 0}, WHITE);

        DrawText(TextFormat("CURRENT FRAME: %i", currentFrame),
                 screenW / 2.0f - 50,
                 0,
                 25,
                 RED);

        DrawFPS(0, 0);

        EndDrawing();
    }

    // Unload the texture from VRAM
    UnloadTexture(coinSpriteSheet);

    CloseWindow();
    return 0;
}