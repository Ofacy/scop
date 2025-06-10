#version 150 core

in vec3 position;

out vec2 texCoords;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection * view * transform * vec4(position, 1.0);
	texCoords = vec2(position.x, position.y) * 0.5 + 0.5; // Map position to texture coordinates
	texCoords.x = texCoords.x * 800.0; // Scale X coordinate for texture width
	texCoords.y = texCoords.y * 600.0; // Scale Y coordinate for texture height
}