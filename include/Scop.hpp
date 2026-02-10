#ifndef SCOP_HPP
# define SCOP_HPP

# include "Texture.hpp"
# include "Mesh.hpp"
# include "TransformableShaderProgram.hpp"
# include "TransitionShaderProgram.hpp"
# include "Mat4.hpp"

# include <optional>
# include <vector>

class Scop {
private:

	GLuint					_vao;
	GLuint					_vbo;
	GLuint					_ebo;
	GLuint					_fbos[2];
	GLuint					_frameTextures[4];
	int						_frameTextureOffset;

	Mesh					&_mesh;
	Texture					*texture;

	TransformableShaderProgram	*_shaderPrograms;
	TransitionShaderProgram		_transitionProgram;
	size_t						_shaderProgramCount;
	size_t						_previousActiveProgramIndex;
	size_t						_activeProgramIndex;
	float						_lastProgramChange;
	GLenum						_drawMode;

	const Mat4				_projectionMatrix;
	Mat4					_transformMatrix;
	Mat4					_viewMatrix;
	
	void _initGPUBuffers();
	void _initTransitionProgram();
	
	void _zoom(float yScroll, float zoomMultiplier);
	void _nextProgram();

	void _handleMovement(Window &window, float deltaTime);

public:
	Scop(Mesh &mesh, Texture *texture, unsigned char rgb[3]);
	~Scop();

	void 						start();
	TransformableShaderProgram	&getActiveShaderProgram();
	TransformableShaderProgram	&getPreviousActiveShaderProgram();
};

#endif
