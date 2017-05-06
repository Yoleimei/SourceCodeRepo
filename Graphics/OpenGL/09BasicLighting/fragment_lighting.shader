#version 330 core

in vec3 midFragPos;
in vec3 midNormal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 color;

void main()
{
	float ambientCoeff = 0.5f;
	vec3 ambient = ambientCoeff * lightColor;

	float diffCoeff = 0.8f;
	vec3 norm = normalize(midNormal);
	vec3 lightDir = normalize(lightPosition - midFragPos);
	diffCoeff = diffCoeff * max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffCoeff * lightColor;

	float specularCoeff = 1.0f;
	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	specularCoeff = specularCoeff * pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularCoeff * lightColor;

	color = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}
