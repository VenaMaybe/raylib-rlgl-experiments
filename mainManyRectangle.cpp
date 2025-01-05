#include "raylib.h"
#include "rlgl.h"
#include <vector>
#include <cstdlib> // For rand()

struct RectangleInstance {
    Vector2 position;
    Color color;
};

// Function to generate a random color
Color GetRandomColor() {
    return Color{ static_cast<unsigned char>(rand() % 256),
                  static_cast<unsigned char>(rand() % 256),
                  static_cast<unsigned char>(rand() % 256),
                  255 };
}

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Batch Rendering Example in C++");
    SetTargetFPS(60);

    const int instanceCount = 100000;
    std::vector<RectangleInstance> instances;
    instances.reserve(instanceCount);

    // Initialize instances with random positions and colors
    for (int i = 0; i < instanceCount; ++i) {
        RectangleInstance inst;
        inst.position = Vector2{ static_cast<float>(GetRandomValue(0, screenWidth)),
                                 static_cast<float>(GetRandomValue(0, screenHeight)) };
        inst.color = GetRandomColor();
        instances.emplace_back(inst);
    }

    while (!WindowShouldClose())
    {
        // Update logic can go here (e.g., moving rectangles)

        // Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Start batch
            rlPushMatrix(); // Save the current transformation matrix
            rlBegin(RL_QUADS);
            for (const auto& inst : instances) {
                rlColor4ub(inst.color.r, inst.color.g, inst.color.b, inst.color.a);

                rlVertex2f(inst.position.x, inst.position.y);
                rlVertex2f(inst.position.x, inst.position.y + 5);
                rlVertex2f(inst.position.x + 5, inst.position.y + 5);
                rlVertex2f(inst.position.x + 5, inst.position.y);
            }
            rlEnd();
            rlPopMatrix(); // Restore the transformation matrix

            DrawRectangle(0,0,50,30,BLACK);
            DrawFPS(10, 10);
        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}
