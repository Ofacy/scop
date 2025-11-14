#version 150 core

flat in int vertexID;
out vec4 outColor;

uniform ivec3 shadeCount;

void main()
{
    vec3 shade = vec3(shadeCount.x, shadeCount.y, shadeCount.z);
    outColor = vec4(shade / 255,
                    1.0);
}
