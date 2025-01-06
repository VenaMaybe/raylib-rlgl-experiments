#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>

int main() {
	const int screenWidth = 800;
    const int screenHeight = 600;
	Vector2 resolutionScreen = { (float)screenWidth, (float)screenHeight };
	Vector2 resolutionTex = { (float)(700), (float)(500) };
	float time = 0.0f;
	int frame = 0;

	// Initialize the window and set up raylib
	InitWindow(screenWidth, screenHeight, "Pixel Sort v1");
	SetTargetFPS(30);

	// 1) Load the implementation
	Shader shader = LoadShader(nullptr, "pixelSorterV1.fs");

		// Get the uniforms for shader
		int resolutionLoc = GetShaderLocation(shader, "u_resolution"); // grabs u_resolution location
		SetShaderValue(shader, resolutionLoc, &resolutionTex, SHADER_UNIFORM_VEC2); // passes resolution to u_resolution

		int bufferLoc = GetShaderLocation(shader, "iChannel0");

	// 2) Create the texture buffer
	Shader bufferA = LoadShader(nullptr, "pixelSorterV1bufferA.fs");
	RenderTexture2D bufferA_Texture2D_Ping = LoadRenderTexture(resolutionTex.x, resolutionTex.y);
	RenderTexture2D bufferA_Texture2D_Pong = LoadRenderTexture(resolutionTex.x, resolutionTex.y);

		// Get the uniforms for bufferA
		int frameLoc = GetShaderLocation(bufferA, "u_frame"); // grabs u_time location
		SetShaderValue(bufferA, frameLoc, &frame, SHADER_UNIFORM_INT); //passes time to u_time

		int resolutionLocBufferA = GetShaderLocation(bufferA, "u_resolution");
		SetShaderValue(bufferA, resolutionLocBufferA, &resolutionTex, SHADER_UNIFORM_VEC2); // passes resolution to u_resolution

		Texture2D imageToSort = LoadTexture("london.png");
		int imageToSortLoc = GetShaderLocation(bufferA, "u_imageToSort");

		int selfLoc = GetShaderLocation(bufferA, "u_self");

	// Begin the frame
	while (!WindowShouldClose()) {
		// Update the time
		time = (float)GetTime();

		RenderTexture2D srcTex;
		RenderTexture2D dstTex;

		if (frame % 2 == 0) {
			srcTex = bufferA_Texture2D_Ping;
			dstTex = bufferA_Texture2D_Pong;
		} else {
			srcTex = bufferA_Texture2D_Pong;
			dstTex = bufferA_Texture2D_Ping;
		}

		// Render the buffer
		BeginTextureMode(dstTex);
		 	ClearBackground(BLACK);

			BeginShaderMode(bufferA);	// Enable custom shader for next shapes
				// Feed it back into itself
				SetShaderValueTexture(bufferA, selfLoc, srcTex.texture);

				SetShaderValueTexture(bufferA, imageToSortLoc, imageToSort); // Set the ID and bind the texture!

				// Da rectangle
				DrawRectangle(50, 50, resolutionTex.x, resolutionTex.y, WHITE);
			EndShaderMode();
		EndTextureMode();

		// Draw
		BeginDrawing();
			ClearBackground(WHITE);

			//DrawTexture(imageToSort, 0, 0, WHITE);
			BeginShaderMode(shader);
				SetShaderValueTexture(shader, bufferLoc, dstTex.texture);
		 		DrawRectangle(50, 50, resolutionTex.x, resolutionTex.y, ORANGE);
		 	EndShaderMode();
		EndDrawing();

		// Update the frame
		frame++;
		SetShaderValue(bufferA, frameLoc, &frame, SHADER_UNIFORM_INT);
	}

	UnloadShader(shader);
	UnloadShader(bufferA);
	UnloadTexture(imageToSort);

	CloseWindow(); // Close the window
	return 0;
}