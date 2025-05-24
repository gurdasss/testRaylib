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

        static Vector2 s_force{0, -50};
        constexpr float ballMass{1.0f};
        static Vector2 s_acceleration{0, s_force.y / ballMass};

        static Vector2 s_velocity{0, 0};

        s_acceleration.x = s_force.x / ballMass;
        s_velocity.x += s_acceleration.x * delta;
        ball.setX(ball.getX() + s_velocity.x * delta);

        s_velocity.y += s_acceleration.y * delta;
        ball.setY(ball.getY() + s_velocity.y * delta);

        constexpr float gravity{9.8f * 1};
        s_acceleration.y += gravity * delta;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ball.getPosition(), ball.getRadius(), ball.getTint());

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
