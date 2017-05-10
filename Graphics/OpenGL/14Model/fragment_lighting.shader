#version 330 core

in vec3 midFragPos;
in vec3 midNormal;
in vec2 midTexture;

// Material
uniform sampler2D material_diffuse;
uniform sampler2D material_specular;
uniform sampler2D material_emission;
uniform float material_shininess;

// Directional Light
uniform vec3 dir_light_direction;
uniform vec3 dir_light_ambient;
uniform vec3 dir_light_diffuse;
uniform vec3 dir_light_specular;

#define POINT_LIGHTS_NUM 4
// Point Light
uniform vec3 ptr_light_position[POINT_LIGHTS_NUM];
uniform vec3 ptr_light_ambient[POINT_LIGHTS_NUM];
uniform vec3 ptr_light_diffuse[POINT_LIGHTS_NUM];
uniform vec3 ptr_light_specular[POINT_LIGHTS_NUM];
uniform float ptr_light_constant[POINT_LIGHTS_NUM];
uniform float ptr_light_linear[POINT_LIGHTS_NUM];
uniform float ptr_light_quadratic[POINT_LIGHTS_NUM];

// Spot Light
uniform vec3 spt_light_position;
uniform vec3 spt_light_direction;
uniform vec3 spt_light_ambient;
uniform vec3 spt_light_diffuse;
uniform vec3 spt_light_specular;
uniform float spt_light_constant;
uniform float spt_light_linear;
uniform float spt_light_quadratic;
uniform float spt_light_cutoff;
uniform float spt_light_outerCutoff;

uniform vec3 viewPosition;

out vec4 color;

vec3 CalcDirLight(vec3 light_direction, vec3 light_ambient, vec3 light_diffuse, vec3 light_specular)
{
	// Directional Light
	vec3 ambient_dir = light_ambient * vec3(texture(material_diffuse, midTexture));

	vec3 norm = normalize(midNormal);
	vec3 lightDir_dir = normalize(-light_direction);
	float diff_dir = max(dot(norm, lightDir_dir), 0.0);
	vec3 diffuse_dir = light_diffuse * diff_dir * vec3(texture(material_diffuse, midTexture));

	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir_dir = reflect(-lightDir_dir, norm);
	float spec_dir = pow(max(dot(viewDir, reflectDir_dir), 0.0), material_shininess);
	vec3 specular_dir = light_specular * spec_dir * vec3(texture(material_specular, midTexture));

	return (ambient_dir + diffuse_dir + specular_dir);
}

vec3 CalcPtrLight(vec3 light_position, vec3 light_ambient, vec3 light_diffuse, vec3 light_specular, float light_constant, float light_linear, float light_quadratic)
{
	// Point Light
	float distance = length(light_position - midFragPos);
	float attenuation = 1.0f / (light_constant + light_linear * distance + light_quadratic * distance * distance);

	vec3 ambient_ptr = light_ambient * vec3(texture(material_diffuse, midTexture));

	vec3 norm = normalize(midNormal);
	vec3 lightDir_ptr = normalize(light_position - midFragPos);
	float diff_ptr = max(dot(norm, lightDir_ptr), 0.0);
	vec3 diffuse_ptr = light_diffuse * diff_ptr * vec3(texture(material_diffuse, midTexture));

	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir_ptr = reflect(-lightDir_ptr, norm);
	float spec_ptr = pow(max(dot(viewDir, reflectDir_ptr), 0.0), material_shininess);
	vec3 specular_ptr = light_specular * spec_ptr * vec3(texture(material_specular, midTexture));

	return (ambient_ptr + diffuse_ptr + specular_ptr);
}

vec3 CalcSptLight(vec3 light_position, vec3 light_direction, vec3 light_ambient, vec3 light_diffuse, vec3 light_specular, float light_constant, float light_linear, float light_quadratic,
	float light_cutoff, float light_outerCutoff)
{
	// Spot Light
	float distance = length(light_position - midFragPos);
	float attenuation = 1.0f / (light_constant + light_linear * distance + light_quadratic * distance * distance);

	vec3 ambient_spt = light_ambient * vec3(texture(material_diffuse, midTexture));

	vec3 norm = normalize(midNormal);
	vec3 lightDir_spt = normalize(light_position - midFragPos);
	float diff_spt = max(dot(norm, lightDir_spt), 0.0);
	vec3 diffuse_spt = light_diffuse * diff_spt * vec3(texture(material_diffuse, midTexture));

	vec3 viewDir = normalize(viewPosition - midFragPos);
	vec3 reflectDir_spt = reflect(-lightDir_spt, norm);
	float spec_spt = pow(max(dot(viewDir, reflectDir_spt), 0.0), material_shininess);
	vec3 specular_spt = light_specular * spec_spt * vec3(texture(material_specular, midTexture));

	float theta = dot(lightDir_spt, normalize(-light_direction));
	float epsilon = light_cutoff - light_outerCutoff;
	float intensity = clamp((theta - light_outerCutoff) / epsilon, 0.0f, 1.0f);
	return (ambient_spt + diffuse_spt + specular_spt) * intensity;
}

void main()
{
	vec3 result = CalcDirLight(dir_light_direction, dir_light_ambient, dir_light_diffuse, dir_light_specular);
	for (int i = 0; i < POINT_LIGHTS_NUM; i++)
		result += CalcPtrLight(ptr_light_position[i], ptr_light_ambient[i], ptr_light_diffuse[i], ptr_light_specular[i], ptr_light_constant[i], ptr_light_linear[i], ptr_light_quadratic[i]);
	result += CalcSptLight(spt_light_position, spt_light_direction, spt_light_ambient, spt_light_diffuse, spt_light_specular, spt_light_constant, spt_light_linear, spt_light_quadratic,
		spt_light_cutoff, spt_light_outerCutoff);

	color = vec4(result, 1.0f);
	// vec3 emission = vec3(texture(material_emission, midTexture));
	// color = vec4(ambient + diffuse + specular + emission, 1.0f);
}
