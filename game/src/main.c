#include "raylib.h"
#include <math.h>

Vector2 lerp(Vector2 start, Vector2 end, float t);
float lerp_float(float start, float end, float t);

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Smooth Movement and Scaling - raylib");

    Vector2 position = {(float)screenWidth / 2, (float)screenHeight / 2};
    Vector2 targetPosition = position;
    float scale = 1.0f;
    float targetScale = scale;
    const float speed = 0.2f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update target position and scale continuously
        targetPosition = GetMousePosition();
        targetScale = 1.0f + (fabs(targetPosition.x - position.x) / 50.0f + fabs(targetPosition.y - position.y) / 50.0f);

        // Interpolate position and scale
        position = lerp(position, targetPosition, speed);
        scale = lerp_float(scale, targetScale, speed);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(position, 20 * scale, MAROON);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

Vector2 lerp(Vector2 start, Vector2 end, float t)
{
    return (Vector2){start.x + t * (end.x - start.x), start.y + t * (end.y - start.y)};
}

float lerp_float(float start, float end, float t)
{
    return start + t * (end - start);
}
