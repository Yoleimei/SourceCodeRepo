#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

out vec3 midColor;
out vec2 midTexCoord;

void main()
{
	gl_Position = vec4(inPosition, 1.0f);
	midColor = inColor;
	midTexCoord = vec2(inTexCoord.x, inTexCoord.y);
}

// clockwise rotate a degree
// [ cos(a)  sin(a)]
// [-sin(a)  cos(a)]

// anticlockwise rotate a degree
// [ cos(a) -sin(a)]
// [ sin(a)  cos(a)]

// clockwise rotate 90 degree
// [ 0  1]
// [-1  0]

// clockwise rotate 180 degree
// [-1  0]
// [ 0 -1]

// anticlockwise rotate 90 degree
// [ 0 -1]
// [ 1  0]

// x-axis mirror
// [ 1  0]
// [ 0 -1]

// y-axis mirror
// [-1  0]
// [ 0  1]

// y=x mirror
// [ 0  1]
// [ 1  0]

// y=-x mirror
// [ 0 -1]
// [-1  0]