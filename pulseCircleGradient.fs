#version 460 core

//in vec4 fragTexCoord;
out vec4 fragColor;

// "little bridges between the CPU and GPU"
uniform float u_time;
uniform vec2 u_resolution;

void main() {
 
	// // Normalized pixel coordinates (from 0 to 1)
	// 	// x and y component changes across screen, (1,1) is top right
	vec2 uv = gl_FragCoord.xy / u_resolution.xy; // 0 <> 1. (range)

	uv -= .5; // remaps the range  from -0.5 <> 0.5smh 
    uv.x *= u_resolution.x/u_resolution.y; // compensate for scaling by multiplying by the aspect ratio

    float d = length(uv); // Distance from origin
    float r = 0.3;
    
    // smoothstep(left, right, i) smoothly interpolates between left and right givin i
    float d_remapped = smoothstep(r, 0., d); // Color 0 black <> 1 white
    
    float r_inner = (cos(u_time) + 1.1)/2.;
    
    vec3 col;
    
    if( d_remapped > r_inner) {
        col = vec3(smoothstep(1. , r_inner, d_remapped)); 
    } else {
        col = vec3(smoothstep(0.0, r_inner, d_remapped));
    }

    

	fragColor = vec4(vec3(col), 1.);
}