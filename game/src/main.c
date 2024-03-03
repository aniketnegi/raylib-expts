#include "raylib.h"
#include <math.h>

Vector2 lerp(Vector2 start, Vector2 end, float t);
float lerp_float(float start, float end, float t);

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Smooth Movement and Scaling - raylib");

    Vector2 position1 = {(float)screenWidth / 2, (float)screenHeight / 2};
    Vector2 targetPosition1 = position1;
    Vector2 position2 = {(float)screenWidth / 3, (float)screenHeight / 3};
    Vector2 targetPosition2 = position2;
    float scale1 = 1.0f;
    float targetScale1 = scale1;
    float scale2 = 1.0f;
    float targetScale2 = scale2;
    float speed = 10.0f;
    float interpolationSpeed = 0.05f;

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        // Update target position and scale continuously
        if (IsKeyDown(KEY_W))
            targetPosition1.y -= speed;
        if (IsKeyDown(KEY_S))
            targetPosition1.y += speed;
        if (IsKeyDown(KEY_A))
            targetPosition1.x -= speed;
        if (IsKeyDown(KEY_D))
            targetPosition1.x += speed;
        if (IsKeyDown(KEY_UP))
            targetPosition2.y -= speed;
        if (IsKeyDown(KEY_DOWN))
            targetPosition2.y += speed;
        if (IsKeyDown(KEY_LEFT))
            targetPosition2.x -= speed;
        if (IsKeyDown(KEY_RIGHT))
            targetPosition2.x += speed;

        targetScale1 = 1.0f + (fabs(targetPosition1.x - position1.x) / 50.0f + fabs(targetPosition1.y - position1.y) / 50.0f);
        targetScale2 = 1.0f + (fabs(targetPosition2.x - position2.x) / 50.0f + fabs(targetPosition2.y - position2.y) / 50.0f);

        // Interpolate position and scale
        position1 = lerp(position1, targetPosition1, interpolationSpeed);
        position2 = lerp(position2, targetPosition2, interpolationSpeed);
        scale1 = lerp_float(scale1, targetScale1, interpolationSpeed);
        scale2 = lerp_float(scale2, targetScale2, interpolationSpeed);

        // Check collisions

        if (CheckCollisionCircles(position1, 10 * scale1, position2, 10 * scale2))
        {
            // Implement collisions
            targetPosition1 = position1;
            targetPosition2 = position2;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(position1, 10 * scale1, MAROON);
        DrawCircleV(position2, 10 * scale2, LIME);

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
