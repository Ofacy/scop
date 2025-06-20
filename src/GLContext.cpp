#include "Window.hpp"
#include "GLContext.hpp"
#include <iostream>

GLContext *GLContext::instance = nullptr;

void glfw_error_callback(int error, const char *description) {
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

GLContext::GLContext() {
}

GLContext &GLContext::getInstance() {
	if (!instance) {
		instance = new GLContext();
	}
	return *instance;
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

	glfwSetErrorCallback(glfw_error_callback);
	
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

void GLContext::pollEvents() {
	this->window.scrollXOffset = 0.0;
	this->window.scrollYOffset = 0.0;
	glfwPollEvents();
}
