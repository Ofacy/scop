#ifndef TRANSITION_SHADER_PROGRAM_HPP
# define TRANSITION_SHADER_PROGRAM_HPP

# include "TransformableShaderProgram.hpp"

# define TANSITION_VARIABLE_NAME "transition"

class TransitionShaderProgram : public TransformableShaderProgram {
private:
	GLint _transitionLocation;

public:
	TransitionShaderProgram();

	void link() override;

	void setTransition(float transition) const;
	void setFrameBufferTextures(GLuint firstTextureUnit, GLuint secondTextureUnit) const;
};

#endif
