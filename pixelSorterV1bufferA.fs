#version 460 core

#define EVEN(x) (( (x) % 2 )==0)
#define ODD(x)  (( (x) % 2 )!=0)

//in vec4 fragTexCoord;
out vec4 fragColor;

// "little bridges between the CPU and GPU"
uniform int u_frame;
uniform vec2 u_resolution;
uniform sampler2D u_imageToSort;

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
	fragColor = texture(u_imageToSort, -uv);

//	fragColor = vec4(uv.x, uv.y, 0., 1.);
//	fragColor = vec4(1.0, 0.47, 0.92, 1.0);

    // Initalize first frame
    /*if (u_frame == 0 || true) {
        //uv.x *= iResolution.x/iResolution.y; // Get the right proportion
        //uv *= 0.2; // zooms in
        fragColor = texture(imageToSort, uv);
        return;
    }

	/*
    ivec2 iTexSize = textureSize(iChannel1, 0); // get the size
    
    vec2 fTexSize = vec2(iTexSize);
    
    // Integer texture coordinates
    ivec2 texCoord = ivec2(uv * fTexSize);
    
    // Causes some out of bounds issues though
    ivec2 texCoordAbove = texCoord + ivec2(0, 1);
    ivec2 texCoordBelow = texCoord - ivec2(0, 1);
    
    // Clamp the coordinates to prevent out-of-bounds access
    texCoordAbove = clamp(texCoordAbove, ivec2(0, 0), iTexSize - ivec2(1, 1));
    texCoordBelow = clamp(texCoordBelow, ivec2(0, 0), iTexSize - ivec2(1, 1));
    
    vec4 current = texelFetch(iChannel1, texCoord, 0); // current pixel
    vec4 above = texelFetch(iChannel1, texCoordAbove, 0);
    vec4 below = texelFetch(iChannel1, texCoordBelow, 0);
    
    // REMEMBER:
    //    You can only change the pixel you're looking at
    
    if (ODD(iFrame)) { // iFrame odd
        if (EVEN(texCoord.y)) {
            if( f(current) == min( f(current), f(above) ))
                current = above;
        }
        if (ODD(texCoord.y)) {
            if( f(current) == max( f(current), f(below) ))
                current = below;
        }
    }
    
    if (EVEN(iFrame)) { // iFrame even  
        if (EVEN(texCoord.y)) {
            if( f(current) == max( f(current), f(below) ))
                current = below;
        }
        if (ODD(texCoord.y)) {
            if( f(current) == min( f(current), f(above) ))
                current = above;
        }
    }


    fragColor = current;
	*/
}