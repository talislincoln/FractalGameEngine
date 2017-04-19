#version 400 core

in vec2 pass_textureCoords;
in float pass_brightness;
in vec2 pass_pos;

in vec3 surfaceNormal; //ambient light 
in vec3 toLightVector; //ambient light

in vec3 toCameraVector; //for reflectiveness

out vec4 color;

uniform sampler2D diffuseMap;

uniform vec3 lightColour;
uniform float shineDamper;
uniform float reflectivity;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.0);
	vec3 diffuse = brightness * lightColour;

	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * lightColour;

	color = vec4(diffuse, 1.0) * texture(diffuseMap, pass_textureCoords) + vec4(finalSpecular, 1.0);
}