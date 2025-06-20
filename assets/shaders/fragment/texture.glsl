#version 150 core

in vec2 texCoords;

out vec4 outColor;

uniform sampler2D textureSampler;

void main()
{
	// Sample the texture at the given texture coordinates
	vec4 sampledColor = texture(textureSampler, texCoords);
	
	// Output the sampled color
	outColor = sampledColor;
}
