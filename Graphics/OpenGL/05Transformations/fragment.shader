#version 330 core

in vec3 midColor;
in vec2 midTexCoord;

out vec4 outColor;

uniform float uniMixValue;

uniform sampler2D uniTexture1;
uniform sampler2D uniTexture2;

void main()
{
	outColor = mix(texture(uniTexture1, midTexCoord), texture(uniTexture2, midTexCoord), uniMixValue);
}
