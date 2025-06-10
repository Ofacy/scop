#version 150 core

in vec2 texCoords;

out vec4 outColor;

uniform sampler2D textureSampler;

void main()
{
	outColor = texture(textureSampler, texCoords.xy / vec2(800, 600));
}