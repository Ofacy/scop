#include "TransformableShaderProgram.hpp"

TransformableShaderProgram::TransformableShaderProgram() : ShaderProgram() {

}

void TransformableShaderProgram::link() {
	ShaderProgram::link();
	this->_transformLocation = this->getUniformLocation(TRANFORM_VARIABLE_NAME);
	this->_viewLocation = this->getUniformLocation(VIEW_VARIABLE_NAME);
	this->_projectionLocation = this->getUniformLocation(PROJECTION_VARIABLE_NAME);
}

void TransformableShaderProgram::setTransform(const Mat4 &value) {
	this->setUniformMat4(this->_transformLocation, value);
}

void TransformableShaderProgram::setProjection(const Mat4 &value) {
	this->setUniformMat4(this->_projectionLocation, value);
}

void TransformableShaderProgram::setView(const Mat4 &value) {
	this->setUniformMat4(this->_viewLocation, value);
}
