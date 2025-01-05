#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>

int main() {
	const int screenWidth = 800;
    const int screenHeight = 600;
	Vector2 resolution = { (float)screenWidth, (float)screenHeight };

	// Initialize the window and set up raylib
	InitWindow(screenWidth, screenHeight, "Pixel Sort v1");
	SetTargetFPS(30);

	// 1) Load the implementation
	Shader shader = LoadShader(nullptr, "pixelSorterV1.fs");

		// Get the uniforms for shader
		float time = 0.0f;
		int timeLoc = GetShaderLocation(shader, "u_time"); // grabs u_time location
		SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT); //passes time to u_time

		int resolutionLoc = GetShaderLocation(shader, "u_resolution"); // grabs u_resolution location
		SetShaderValue(shader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2); // passes resolution to u_resolution

		int bufferLoc = GetShaderLocation(shader, "iChannel0");

	// 2) Create the texture buffer
	Shader bufferA = LoadShader(nullptr, "pixelSorterV1bufferA.fs");
//	RenderTexture2D bufferA_Texture2D = LoadRenderTexture(screenWidth, screenHeight);

		// Get the uniforms for bufferA
		int frame = 0;
		int frameLoc = GetShaderLocation(bufferA, "u_frame"); // grabs u_time location
		SetShaderValue(bufferA, frameLoc, &frame, SHADER_UNIFORM_INT); //passes time to u_time

		int resolutionLocBufferA = GetShaderLocation(bufferA, "u_resolution");
		SetShaderValue(bufferA, resolutionLocBufferA, &resolution, SHADER_UNIFORM_VEC2); // passes resolution to u_resolution

		Texture2D imageToSort = LoadTexture("london.png");
		int imageToSortLoc = GetShaderLocation(bufferA, "u_imageToSort");

	// Begin the frame
	while (!WindowShouldClose()) {
		// Update the time
		time = (float)GetTime();
		SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

		// 4) Render the buffer
		// BeginTextureMode(bufferA_Texture2D);
		// 	ClearBackground(BLACK);

		// 	BeginShaderMode(bufferA);
		// 		DrawRectangle(50, 50, screenWidth - 100, screenHeight - 100, ORANGE);
		// 	EndShaderMode();

		// EndTextureMode();

		// SetShaderValueTexture(shader, bufferLoc, bufferA_Texture2D.texture);

		// Draw
		BeginDrawing();
			ClearBackground(WHITE);

			//DrawTexture(imageToSort, 0, 0, WHITE);


			BeginShaderMode(bufferA);	// Enable custom shader for next shapes
				SetShaderValueTexture(bufferA, imageToSortLoc, imageToSort); // Set the ID and bind the texture!


				DrawRectangle(50, 50, screenWidth - 100, screenHeight - 100, WHITE);
			EndShaderMode();
		EndDrawing();

		// Update the frame
		frame++;
	}

//	UnloadShader(shader);
	UnloadShader(bufferA);
	UnloadTexture(imageToSort);

	CloseWindow(); // Close the window
	return 0;
}