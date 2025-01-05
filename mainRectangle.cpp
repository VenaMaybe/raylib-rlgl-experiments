#include "raylib.h"
#include "rlgl.h"

int main() {
	// Initialize the window and set up raylib
	InitWindow(800, 600, "RLGL Triangle Example");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Begin a custom drawing mode
		rlPushMatrix(); // Save the current transformation matrix

		rlBegin(RL_QUADS); // Specify we want to draw triangles
		rlColor3f(1.0f, 0.0f, 0.0f); // Set color to red

		// Specify the three vertices of the triangle
		rlVertex2f(100.0f, 100.0f); // Top-left vertex
		rlVertex2f(100.0f, 400.0f); // Bottom-left vertex
		rlVertex2f(400.0f, 400.0f); // Bottom-right vertex
		rlVertex2f(400.0f, 100.0f); // Top-right vertex

		rlEnd(); // End the drawing of the triangle

		rlPopMatrix(); // Restore the transformation matrix

		EndDrawing();
	}

	CloseWindow(); // Close the window
	return 0;
}
