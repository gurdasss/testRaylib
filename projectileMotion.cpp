#include "Circle2D.h"
#include <raylib.h>

int main()
{
    constexpr int screenW{800 * 2};
    constexpr int screenH{450 * 2};

    InitWindow(screenW, screenH, "TEST");

    SetTargetFPS(60);

    Circle2D ball{};
    ball.setPosition(Vector2{100, screenH / 2});
    ball.setRadius(20);
    ball.setTint(BLUE);

    [[maybe_unused]] constexpr float delta{1.0f / 60.0f};

    while (!WindowShouldClose())
    {
        // Force -> Acceleration
        // Acceleration -> Velocity
        // Velocity -> Change in movement

        // force towards x-axis (can be +ve, -ve, or 0)
        constexpr float xForce{2};
        constexpr float ballMass{2.0f};

        // acceleration towards x-axis (can be +ve, -ve, or 0)
        // acceleration = force / mass
        static float s_xAcceleration{xForce / ballMass};

        // velocity towards x-axis (can be +ve, -ve, or 0)
        static float s_xVelocity{0};

        // if acceleration increases, then velocity also increases
        // if acceleration is zero, then velocity stays the same
        // if acceleration decreases, then velocity also decreases
        // delta is multiplied to get consistent movement across
        // different FPSs
        s_xVelocity += s_xAcceleration * delta;

        // applying velocity towards x-axis
        ball.setX(ball.getX() + s_xVelocity * delta);

        // force towards y-axis (can be +ve, -ve, or 0)
        constexpr float yForce{0};

        // acceleration towards y-axis (can be +ve, -ve, or 0)
        // acceleration = force / mass
        static float s_yAcceleration{yForce / ballMass};

        // velocity towards y-axis (can be +ve, -ve, or 0)
        static float s_yVelocity{0};

        // gravitational acceleration that always pulls
        // any object's Y velocity downwards
        // gravitational acceleration only affects
        // vertical velocity ONLY
        constexpr float gravity{9.8f * 20};

        // if acceleration increases, then velocity also increases
        // if acceleration is zero, then velocity stays the same
        // if acceleration decreases, then velocity also decreases
        // delta is multiplied to get consistent movement across
        // different FPSs
        s_yVelocity += s_yAcceleration * delta;

        // as mentioned above, gravitational acceleration
        // always affects any object's Y velocity ONLY
        s_yAcceleration += gravity * delta;

        // applying velocity towards y-axis
        ball.setY(ball.getY() + s_yVelocity * delta);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ball.getPosition(), ball.getRadius(), ball.getTint());

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#if 0

        // speed is a scalar quantity
        // which means it only have magnitude
        // speed can never be negative

        // velocity is a vector quantity
        // which means it have magnitude and direction
        // velocity can be negative and positive
        static float s_xVelocity{0};
        static float s_yVelocity{0};

        constexpr float ballMass{1.0f};
        constexpr float xForce{2000};

        constexpr float xAcceleration{xForce / ballMass};
        // a constant gravitational acceleration
        constexpr float gravity{9.8f * 100};

        s_xVelocity += xAcceleration * delta;
        s_yVelocity += gravity * delta;

        // multiplied delta for consistent movement across different
        // machines and FPS
        ball.setX(ball.getX() + s_xVelocity * delta);
        ball.setY(ball.getY() + s_yVelocity * delta);

#endif