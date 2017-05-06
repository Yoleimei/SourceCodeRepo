#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
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
in vec2 midTexture;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

out vec4 color;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, midTexture));

	vec3 norm = normalize(midNormal);
	vec3 lightDir = normalize(light.position - midFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, midTexture));

	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, midTexture));

	vec3 emission = vec3(texture(material.emission, midTexture));

	color = vec4(ambient + diffuse + specular + emission, 1.0f);
}
