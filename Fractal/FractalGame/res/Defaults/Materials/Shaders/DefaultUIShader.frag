#version 140

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D UITexture;
void main(void){

	out_Color = texture(UITexture,textureCoords);

}