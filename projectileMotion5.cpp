#include "Line2D.h"
#include "Circle2D.h"
#include <raylib.h>
#include <raymath.h> // for VectorLineAngle()
#include <iostream>
#include <cmath> // for std::cos & std::sin

int main()
{
    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "TEST");

    SetTargetFPS(60);

    Circle2D ball{};
    ball.setRadius(20);
    ball.setTint(BLUE);
    ball.setPosition(Vector2{100, screenH - ball.getRadius()});

    Vector2 velocity{};

    // increasing the power of gravitational acceleration
    constexpr float gravityPower{100};
    constexpr float gravity{9.8f * gravityPower};

    Vector2 acceleration{0, gravity};

    Line2D arrow{};
    arrow.setTint(RED);
    arrow.setStartPos(ball.getPosition());

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            arrow.setEndPos(GetMousePosition());
            arrow.setStartPos(ball.getPosition());

            float angleInRadian{
                Vector2LineAngle(ball.getPosition(),
                                 arrow.getEndPos())};

            constexpr float speed{5 * gravityPower};

            std::cout << "Angle in Radian: " << angleInRadian << '\n';
            std::cout << "Angle in Degree: "
                      << (angleInRadian * 180) / PI << '\n';

            // setting the initial velocity
            // dividing the X and Y component of
            // velocity using following formulas:
            // X initial velocity = speed * cos(angleInRadian)
            // because negative Y means upwards direction
            // Y initial velocity = -speed * sin(angleInRadian)
            velocity.x = speed * std::cos(angleInRadian);
            velocity.y = -speed * std::sin(angleInRadian);
        }

        [[maybe_unused]] constexpr float delta{1.0f / 60.0f};

        // bounce factor is between 0.0f to 1.0f
        // 1.0f means that the ball will not lose any
        // energy after hitting the floor
        // 0.0f means that the ball will not bounce at all
        constexpr float bounceFactor{0.9f};

        if (ball.getY() + ball.getRadius() > screenH)
        {
            // std::cout << "Ball Position: " << ball.getY() << '\n';
            // std::cout << "Ball + Height Position: "
            //           << ball.getY() + ball.getRadius() << '\n';
            // std::cout << "Ball's Y Velocity: " << velocity.y << '\n';
            // std::cout << "Ball's Y -Velocity: " << -velocity.y << '\n';

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

            constexpr float friction{50.0f};

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
        else if (ball.getY() - ball.getRadius() < 0)
        {
            velocity.y = -velocity.y * bounceFactor;

            // just want to ensure that just in case
            // we make the gravity negative than the gradational
            // acceleration won't sink the ball "inside" the "ceiling"
            // because the gravitational acceleration
            // will still affect the ball's Y velocity
            ball.setY(ball.getRadius());
        }

        // We got to separately check if the ball had
        // hit the ground and/or also moving towards
        // either left or right walls

        // check if the ball is crossing the screen width
        if (ball.getX() + ball.getRadius() > screenW)
        {
            // invert the velocity's X component
            // before reducing its magnitude (speed)
            // by bounce factor
            velocity.x = -velocity.x * bounceFactor;

            // also make sure to rest the ball's X
            // position just in case user decided
            // to keep applying force towards that direction
            ball.setX(screenW - ball.getRadius());
        }
        else if (ball.getX() - ball.getRadius() < 0)
        {
            // invert the velocity's X component
            // before reducing its magnitude (speed)
            // by bounce factor
            velocity.x = -velocity.x * bounceFactor;

            // also make sure to rest the ball's X
            // position just in case user decided
            // to keep applying force towards that direction
            ball.setX(ball.getRadius());
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
        DrawLineV(arrow.getStartPos(), arrow.getEndPos(), arrow.getTint());

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
