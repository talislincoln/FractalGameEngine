#version 330 core
in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec2 pass_textureCoords;
out float pass_brightness;
out vec2 pass_pos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	pass_textureCoords = texCoord;
    gl_Position = projection * view * model * vec4(position, 1.0f);
}