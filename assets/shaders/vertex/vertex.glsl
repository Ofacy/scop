#version 150 core

in vec3 position;

flat out int vertexID;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection * view * transform * vec4(position, 1.0);
	vertexID = gl_VertexID;
}