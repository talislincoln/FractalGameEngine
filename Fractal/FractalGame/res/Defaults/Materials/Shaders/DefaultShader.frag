#version 330 core //opengl 3's syntax
struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float luster;
};
struct Light{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 colour;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main(){
	//ambient 
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.direction - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	//spec
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.luster);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	//attenuation
	float distance = length(light.direction - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse	*= attenuation;
	specular *= attenuation;
	//
	colour = vec4(ambient + diffuse + specular, 1.0f);
}