#version 330 core
in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec2 pass_textureCoords; //I dunno what this is: talis
out float pass_brightness; //I dunno what this is: talis
out vec2 pass_pos; //I dunno what this is: talis

out vec3 surfaceNormal; //ambient light 
out vec3 toLightVector; //ambient light

uniform vec3 lightPosition;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0);

	pass_textureCoords = texCoord;
    gl_Position = projection * view * worldPosition;

	surfaceNormal = (model * vec4(normal, 0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
}