#include "Window.hpp"
#include "GLContext.hpp"
#include <iostream>
#include <stdexcept>

GLContext *GLContext::instance = nullptr;

void glfw_error_callback(int error, const char *description) {
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	(void) source;
	(void) id;
	(void) severity;
	(void) length;
	(void) userParam;
    std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
}

GLContext::GLContext() : window(1920, 1080) {
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window.init("scop");

	glfwSetErrorCallback(glfw_error_callback);
	
	glfwMakeContextCurrent(window.getHandle());
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		glfwDestroyWindow(window.getHandle());
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD");
	}
	glDebugMessageCallback(MessageCallback, NULL);
}

Window &GLContext::getWindow() {
	return this->window;
}

void GLContext::pollEvents() {
	this->window._scrollXOffset = 0.0;
	this->window._scrollYOffset = 0.0;
	glfwPollEvents();
}
