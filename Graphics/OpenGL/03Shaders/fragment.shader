#version 330 core

in vec4 vertexColor;
out vec4 color;

uniform float myRed;

void main()
{
	color = vec4(myRed, vertexColor.yz, 1.0f);
}
