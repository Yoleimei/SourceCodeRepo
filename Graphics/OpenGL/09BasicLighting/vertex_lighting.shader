#version 330 core
layout(location = 0) in vec3 position;
layout(location = 3) in vec3 inNormal;

uniform mat4 uniModel;
uniform mat4 uniView;
uniform mat4 uniProjection;

out vec3 midNormal;
out vec3 midFragPos;

void main()
{
	gl_Position = uniProjection * uniView * uniModel * vec4(position, 1.0f);
	midFragPos = vec3(uniModel * vec4(position, 1.0f));
	midNormal = mat3(transpose(inverse(uniModel))) * inNormal;
}
