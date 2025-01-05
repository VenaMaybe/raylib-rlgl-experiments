#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>

int main() {
	const int screenWidth = 800;
    const int screenHeight = 600;

	// Initialize the window and set up raylib
	InitWindow(screenWidth, screenHeight, "meow");

	Shader shader = LoadShader(nullptr, "pulseCircleGradient.fs");

	float time = 0.0f;
	int timeLoc = GetShaderLocation(shader, "u_time"); // grabs u_time location
	SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT); //passes time to u_time

	Vector2 resolution = { (float)screenWidth, (float)screenHeight }; // grabs u_resolution location
	int resolutionLoc = GetShaderLocation(shader, "u_resolution");
	SetShaderValue(shader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2); // passes resolution to u_resolution


	while (!WindowShouldClose()) {
		// Update the time
		time = (float)GetTime();
		SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

		// Draw
		BeginDrawing();
			ClearBackground(WHITE);

			BeginShaderMode(shader);	// Enable custom shader for next shapes
				DrawRectangle(50, 50, screenWidth - 100, screenHeight - 100, WHITE);
			EndShaderMode();
		EndDrawing();
	}

	UnloadShader(shader);

	CloseWindow(); // Close the window
	return 0;
}