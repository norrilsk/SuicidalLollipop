#version 330 core

uniform int textures_enabled;
uniform sampler2D textureSampler;

in vec3 fragmentColor;
in vec2 UV;
out vec3 color;


void main()
{
	if (textures_enabled != 0)
		color = texture(textureSampler, UV).xyz;
	else
		color = fragmentColor;
}