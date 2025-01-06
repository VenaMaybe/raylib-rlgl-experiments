#version 460 core

#define EVEN(x) (( (x) % 2 )==0)
#define ODD(x)  (( (x) % 2 )!=0)

//in vec4 fragTexCoord;
out vec4 fragColor;

// "little bridges between the CPU and GPU"
uniform int u_frame;
uniform vec2 u_resolution;
uniform sampler2D u_imageToSort;
uniform sampler2D u_self;

float lum709(vec3 c) {
    return -1. * ((c.r*0.2126) + (c.g*0.7152) + (c.b*0.0722));
}
float avg(vec3 c) {
    return -1. * ((c.r*1.) + (c.g*1.) + (c.b*1.));
}    
float f(vec4 c) {
    return avg(c.rgb);
}

void main() {
    // Normalized pixel coordinates (from 0 to 1)
	vec2 uv = gl_FragCoord.xy / u_resolution.xy; // 0 <> 1. (range)

    // Initalize first frame
    if (u_frame == 0) {
        //uv.x *= iResolution.x/iResolution.y; // Get the right proportion
        //uv *= 0.2; // zooms in
        fragColor = texture(u_imageToSort, -uv);
        return;
    }

    ivec2 iTexSize = textureSize(u_self, 0); // get the size
    
    vec2 fTexSize = vec2(iTexSize);
    
    // Integer texture coordinates
    ivec2 texCoord = ivec2(uv * fTexSize);
    
    // Causes some out of bounds issues though
    ivec2 texCoordAbove = texCoord + ivec2(0, 1);
    ivec2 texCoordBelow = texCoord - ivec2(0, 1);
    
    // Clamp the coordinates to prevent out-of-bounds access
    texCoordAbove = clamp(texCoordAbove, ivec2(0, 0), iTexSize - ivec2(1, 1));
    texCoordBelow = clamp(texCoordBelow, ivec2(0, 0), iTexSize - ivec2(1, 1));

    vec4 current = texelFetch(u_self, texCoord, 0); // current pixel
    vec4 above = texelFetch(u_self, texCoordAbove, 0);
    vec4 below = texelFetch(u_self, texCoordBelow, 0);
    
    // REMEMBER:
    //    You can only change the pixel you're looking at
    
	/*
    if (ODD(u_frame)) { // iFrame odd
        if (EVEN(texCoord.y)) {
            if( f(current) == min( f(current), f(above) ))
                current = above;
        }
        if (ODD(texCoord.y)) {
            if( f(current) == max( f(current), f(below) ))
                current = below;
        }
    }
    
    if (EVEN(u_frame)) { // iFrame even  
        if (EVEN(texCoord.y)) {
            if( f(current) == max( f(current), f(below) ))
                current = below;
        }
        if (ODD(texCoord.y)) {
            if( f(current) == min( f(current), f(above) ))
                current = above;
        }
    }*/

    //fragColor = vec4(uv.x, uv.y, 0., 1.);
	fragColor = current;
}