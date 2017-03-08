#version 330 core

in vec2 pass_textureCoords;
in float pass_brightness;
in vec2 pass_pos;

out vec4 color;

uniform sampler2D diffuseMap;

void main()
{
	color = texture(diffuseMap, pass_textureCoords);
}