#version 150 core

out vec4 outColor;

uniform float transition;
uniform ivec2 windowSize;
uniform sampler2D firstSampler;
uniform sampler2D secondSampler;

void main()
{
	vec2 textureCoord = gl_FragCoord.xy / vec2(windowSize.xy);
	vec3 firstColor = texture(firstSampler, textureCoord).xyz;
	vec3 secondColor = texture(secondSampler, textureCoord).xyz;
    outColor = vec4(secondColor * transition + firstColor * (1 - transition),
                    1.0);
}
