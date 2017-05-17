#version 330 core //opengl 3's syntax
struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float luster;
};
struct DirLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
struct SpotLight{
	vec3 position;
	vec3 direction;

	float cutoff;
	float outerCutoff;

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
uniform DirLight dirlight;
uniform PointLight pointlight;
uniform SpotLight spotlight;

//depth testing
float near = 1.0;
float far = 100.0;
//depth test function
float linearizeDepth(float depth){
	float z = depth * 2.0 - 1.0; //back to NDC
	return (2.0 * near * far) / (far + near - z * (far - near));
}

//functions
vec3 CalcDirLight(DirLight light);
vec3 CalcPointLight(PointLight light);
vec3 CalcSpotLight(SpotLight light);

void main(){
	//directional
	vec3 result = CalcDirLight(dirlight);
	//point
	result += CalcPointLight(pointlight);
	//spec
	result += CalcSpotLight(spotlight);
	//depth
	float depth = linearizeDepth(gl_FragCoord.z) / far;
	//result
	//colour = vec4(result, 1.0);
	colour = vec4(vec3(depth), 1.0); //depth result!
}
vec3 CalcDirLight(DirLight light){
	//ambient 
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	//spec
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.luster);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	//
	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light){
	//ambient 
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	//spec
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.luster);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	//attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	//
	ambient *= attenuation;
	diffuse	*= attenuation;
	specular *= attenuation;
	//
	return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light){
	//ambient 
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	//spec
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.luster);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	//spotlight
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutoff - light.outerCutoff);
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;
	//attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//
	return (ambient + diffuse + specular);
}