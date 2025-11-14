#ifndef SCOP_HPP
# define SCOP_HPP

# include "Texture.hpp"
# include "Mesh.hpp"
# include "TransformableShaderProgram.hpp"
# include "Mat4.hpp"

# include <optional>
# include <vector>

class Scop {
private:

	GLuint					_vao;
	GLuint					_vbo;
	GLuint					_ebo;

	Mesh					&_mesh;

	TransformableShaderProgram	*_shaderPrograms;
	size_t						_shaderProgramCount;
	size_t						_previousActiveProgramIndex;
	size_t						_activeProgramIndex;
	float						_lastProgramChange;
	GLenum						_drawMode;

	const Mat4				_projectionMatrix;
	Mat4					_transformMatrix;
	Mat4					_viewMatrix;
	
	void _initGPUBuffers();
	
	void _zoom(float yScroll, float zoomMultiplier);
	void _nextProgram();

public:
	Scop(Mesh &mesh, bool texture, unsigned char rgb[3]);

	void 						start();
	TransformableShaderProgram	&getActiveShaderProgram();
	TransformableShaderProgram	&getPreviousActiveShaderProgram();
};

#endif
