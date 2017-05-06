#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 midFragPos;
in vec3 midNormal;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

out vec4 color;

void main()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(midNormal);
	vec3 lightDir = normalize(light.position - midFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * material.specular;

	color = vec4(ambient + diffuse + specular, 1.0f);
}
