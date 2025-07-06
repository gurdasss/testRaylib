#include <raylib.h>  // Core raylib types (Vector2)
#include <raymath.h> // raymath helper functions (Vector2Rotate)
#include <iostream>  // For printf

int main(void)
{
    // Our original direction: pointing right on the X‑axis
    Vector2 v = {1.0f, 0.0f}; // (x=1, y=0)

    // Angles we’ll rotate by (in radians):
    //  90°   →  PI/2
    // 180°   →  PI
    // -90°   → -PI/2
    //   0°   →    0
    float angles[4] = {PI / 2, PI, -PI / 2, 0.0f};
    const char *labels[4] = {"90°", "180°", "-90°", "0°"};

    printf("Rotating Vector (1,0):\n");
    for (int i = 0; i < 4; i++)
    {
        Vector2 r = Vector2Rotate(v, angles[i]);
        // Print the rotated vector
        // printf("Radian: %.3f\n", angles[i]);
        printf("  %s → (%.3f, %.3f)\n", labels[i], r.x, r.y);
    }

    return 0;
}
