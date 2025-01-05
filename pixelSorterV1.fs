#version 460 core

//in vec4 fragTexCoord;
out vec4 fragColor;

// "little bridges between the CPU and GPU"
uniform float u_time;
uniform vec2 u_resolution;
uniform sampler2D iChannel0; // like shaderToy

// Main shader
void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;

    // Output to screen
    vec4 bufferA = texture(iChannel0, uv);
    fragColor = bufferA;
}