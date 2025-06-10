#include "Window.hpp"
#include "GLContext.hpp"
#include <iostream>

GLContext::GLContext() {
}

GLContext::~GLContext() {
	this->terminate();
}

void GLContext::terminate() {
	glfwTerminate();

}

void	GLContext::init() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window.init(800, 600, "scop");
	
	glfwMakeContextCurrent(window.getHandle());
	if (!gladLoadGL(glfwGetProcAddress)) {
		glfwDestroyWindow(window.getHandle());
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

Window &GLContext::getWindow() {
	return this->window;
}

void GLContext::pollEvents() const {
	glfwPollEvents();
}
