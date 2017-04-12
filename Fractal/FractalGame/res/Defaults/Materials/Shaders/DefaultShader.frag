#version 330 core

in vec2 pass_textureCoords;
in float pass_brightness;
in vec2 pass_pos;

in vec3 surfaceNormal; //ambient light 
in vec3 toLightVector; //ambient light

out vec4 color;

uniform sampler2D diffuseMap;
uniform vec3 lightColour;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.0);
	vec3 diffuse = brightness * lightColour;

	color = vec4(diffuse, 1.0) * texture(diffuseMap, pass_textureCoords);
}