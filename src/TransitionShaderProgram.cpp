#include "TransitionShaderProgram.hpp"

TransitionShaderProgram::TransitionShaderProgram() : TransformableShaderProgram() {

}

void TransitionShaderProgram::link() {
	TransformableShaderProgram::link();
	Window &window =  GLContext::getInstance().getWindow();
	this->_transitionLocation = this->getUniformLocation(TANSITION_VARIABLE_NAME);
	this->use();
	this->setUniform2i(this->getUniformLocation("windowSize"), window.getWidth(), window.getHeight());
}

void TransitionShaderProgram::setTransition(const float transition) const {
	this->setUniform1f(this->_transitionLocation, transition);
}

void TransitionShaderProgram::setFrameBufferTextures(GLuint firstTextureUnit, GLuint secondTextureUnit) const {
	this->setUniform1i(this->getUniformLocation("firstSampler"), firstTextureUnit);
	this->setUniform1i(this->getUniformLocation("secondSampler"), secondTextureUnit);
}
