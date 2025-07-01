#ifndef TRANSFORMABLE_SHADER_PROGRAM_HPP
# define TRANSFORMABLE_SHADER_PROGRAM_HPP

# include "ShaderProgram.hpp"

# include "Mat4.hpp"

# define TRANFORM_VARIABLE_NAME "transform"
# define VIEW_VARIABLE_NAME "view"
# define PROJECTION_VARIABLE_NAME "projection"

class TransformableShaderProgram : public ShaderProgram {
private:
	GLint _transformLocation;
	GLint _projectionLocation;
	GLint _viewLocation;

public:
	TransformableShaderProgram();

	void link() override;

	void setTransform(const Mat4 &value);
	void setProjection(const Mat4 &value);
	void setView(const Mat4 &value);
};

#endif
