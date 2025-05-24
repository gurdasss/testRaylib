#include "Circle2D.h"
#include <raylib.h>
#include <iostream>
#include <cmath>

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "TEST");

    SetTargetFPS(60);

    Circle2D ball{};
    ball.setPosition(Vector2{100, screenH / 2});
    ball.setRadius(20);
    ball.setTint(BLUE);

    float angle{5};

    // converting angle to radian
    float angleInRadian{angle * (PI / 180)};

    float speed{12 * 50};
    // these following will affect
    // in both x- and y-axises
    // setting the initial velocity
    // dividing the X and Y component of
    // velocity using following formulas:
    // X initial velocity = speed * cos(angleInRadian)
    // because negative Y means upwards direction
    // Y initial velocity = -speed * sin(angleInRadian)
    Vector2 velocity{
        speed * std::cos(angleInRadian),
        -speed * std::sin(angleInRadian),
    };

    // increasing the power of gravitational acceleration
    constexpr float gravityPower{100};
    constexpr float gravity{9.8f * gravityPower};

    Vector2 acceleration{0, gravity};

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_SPACE))
            velocity.y = -5 * gravityPower;
        else if (IsKeyPressed(KEY_RIGHT))
            acceleration.x = 5 * gravityPower;
        else if (IsKeyPressed(KEY_LEFT))
            acceleration.x = -5 * gravityPower;
        else if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))
            acceleration.x = 0;

        [[maybe_unused]] constexpr float delta{1.0f / 60.0f};

        if (ball.getY() + ball.getRadius() > screenH)
        {
            std::cout << "Ball Position: " << ball.getY() << '\n';
            std::cout << "Ball + Height Position: "
                      << ball.getY() + ball.getRadius() << '\n';
            std::cout << "Ball's Y Velocity: " << velocity.y << '\n';
            std::cout << "Ball's Y -Velocity: " << -velocity.y << '\n';

            // bounce factor is between 0.0f to 1.0f
            // 1.0f means that the ball will not lose any
            // energy after hitting the floor
            // 0.0f means that the ball will not bounce at all
            constexpr float bounceFactor{0.9f};

            // once ball hits the ground
            // we need to invert its current Y velocity before
            // reducing its magnitude (speed) by bounce factor
            // each time it hits the ground
            velocity.y = -velocity.y * bounceFactor;

            // lastly, we got to rest the ball's Y position
            // to keep it from sinking "inside" the "ground"
            // because the gravitational acceleration
            // will still affect the ball's Y velocity
            ball.setY(screenH - ball.getRadius());

            constexpr float friction{5.0f};

            // once ball hits the ground we need to apply
            // friction to its X velocity
            if (velocity.x > 0)
            {
                // move the ball's X velocity towards zero
                velocity.x -= friction * delta;

                if (velocity.x < 0)
                    velocity.x = 0;
            }
            else if (velocity.x < 0)
            {
                // move the ball's X velocity towards zero
                velocity.x += friction * delta;

                if (velocity.x > 0)
                    velocity.x = 0;
            }
            else
                std::cout << "X Velocity: " << velocity.x << '\n';
        }

        // ACCELERATION WILL AFFECT VELOCITY ON BOTH AXISES
        // applying acceleration on both the components
        // of the velocity
        // also we need a consistent acceleration across
        // different FPS so we need to scale
        // acceleration accordingly by delta
        velocity.x += acceleration.x * delta;
        velocity.y += acceleration.y * delta;

        // LASTLY, VELOCITY WILL AFFECT THE POSITION OF THE BALL
        // applying the updated velocity on both the
        // position of the ball
        // also we need a consistent movement across
        // different FPS so we need to scale
        // movement accordingly by delta
        ball.setX(ball.getX() + velocity.x * delta);
        ball.setY(ball.getY() + velocity.y * delta);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ball.getPosition(), ball.getRadius(), ball.getTint());

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
