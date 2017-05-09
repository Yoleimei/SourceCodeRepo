#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirectionalLight
{
	// vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutoff;
	float outerCutoff;
};

in vec3 midFragPos;
in vec3 midNormal;
in vec2 midTexture;

uniform vec3 viewPosition;
uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight ptrLight;
uniform SpotLight sptLight;

out vec4 color;

void main()
{
	// Directional Light
	vec3 ambient_dir = dirLight.ambient * vec3(texture(material.diffuse, midTexture));

	vec3 norm = normalize(midNormal);
	vec3 lightDir_dir = normalize(-dirLight.direction);
	float diff_dir = max(dot(norm, lightDir_dir), 0.0);
	vec3 diffuse_dir = dirLight.diffuse * diff_dir * vec3(texture(material.diffuse, midTexture));

	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir_dir = reflect(-lightDir_dir, norm);
	float spec_dir = pow(max(dot(viewDir, reflectDir_dir), 0.0), material.shininess);
	vec3 specular_dir = dirLight.specular * spec_dir * vec3(texture(material.specular, midTexture));

	// Point Light
	float distance = length(ptrLight.position - midFragPos);
	float attenuation = 1.0f / (ptrLight.constant + ptrLight.linear * distance + ptrLight.quadratic * distance * distance);

	vec3 ambient_ptr = ptrLight.ambient * vec3(texture(material.diffuse, midTexture));

	vec3 lightDir_ptr = normalize(ptrLight.position - midFragPos);
	float diff_ptr = max(dot(norm, lightDir_ptr), 0.0);
	vec3 diffuse_ptr = ptrLight.diffuse * diff_ptr * vec3(texture(material.diffuse, midTexture));

	vec3 reflectDir_ptr = reflect(-lightDir_ptr, norm);
	float spec_ptr = pow(max(dot(viewDir, reflectDir_ptr), 0.0), material.shininess);
	vec3 specular_ptr = ptrLight.specular * spec_ptr * vec3(texture(material.specular, midTexture));

	// Spot Light
	vec3 lightDir_spt = normalize(sptLight.position - midFragPos);
	float theta = dot(lightDir_spt, normalize(-sptLight.direction));
	float epsilon = sptLight.cutoff - sptLight.outerCutoff;
	float intensity = clamp((theta - sptLight.outerCutoff) / epsilon, 0.0f, 1.0f);
	vec3 color_spt = sptLight.color * intensity;

	vec3 ambient = ambient_dir + ambient_ptr * attenuation;
	vec3 diffuse = diffuse_dir + diffuse_ptr * attenuation;
	vec3 specular = specular_dir + specular_ptr * attenuation;
	// vec3 emission = vec3(texture(material.emission, midTexture));
	// color = vec4(color_spt, 1.0f);
	color = vec4(ambient + diffuse + specular + color_spt, 1.0f);
	// color = vec4(ambient + diffuse + specular + emission, 1.0f);
}
