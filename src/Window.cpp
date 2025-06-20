#include "GLContext.hpp"
#include "Window.hpp"
#include <stdexcept>
#include <iostream>

void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	GLContext &glContext = GLContext::getInstance();
	Window &win = glContext.getWindow();
	if (win.getHandle() == window) {
		win.scrollXOffset += xoffset;
		win.scrollYOffset += yoffset;
	} else {
		std::cerr << "Scroll callback received for a different window." << std::endl;
	}
}

Window::Window() : window(nullptr) {
}

Window::Window(GLFWwindow* win) : window(win) {
}

Window::~Window() {
	if (this->window) {
		glfwDestroyWindow(this->window);
	}
}

Window& Window::operator=(const Window& other) {
	if (this != &other) {
		if (this->window) {
			glfwDestroyWindow(this->window);
		}
		this->window = other.window;
	}
	return *this;
}

void Window::init(int width, int height, const char* title) {
	if (!this->window) {
		this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!this->window) {
			throw std::runtime_error("Failed to create GLFW window");
		}
		glfwSetScrollCallback(this->window, glfw_scroll_callback);
		glfwMakeContextCurrent(this->window);
	}
}

GLFWwindow* Window::getHandle() const {
	return this->window;
}

void Window::swapBuffers() const {
	if (this->window) {
		glfwSwapBuffers(this->window);
	}
}

bool Window::shouldClose() const {
	if (this->window) {
		return glfwWindowShouldClose(this->window);
	}
	return true; // If window is not initialized, consider it as closed
}

void Window::setShouldClose(bool value) {
	if (this->window) {
		glfwSetWindowShouldClose(this->window, value);
	}
}

int Window::getKey(int key) const {
	if (this->window) {
		return glfwGetKey(this->window, key);
	}
	return GLFW_RELEASE; // If window is not initialized, return released state
}

int Window::getMouseButton(int button) const {
	if (this->window) {
		return glfwGetMouseButton(this->window, button);
	}
	return GLFW_RELEASE; // If window is not initialized, return released state
}

void Window::getCursorPos(double &xpos, double &ypos) const {
	if (this->window) {
		glfwGetCursorPos(this->window, &xpos, &ypos);
	} else {
		xpos = 0.0;
		ypos = 0.0; // If window is not initialized, return default position
	}
}

void Window::setCursorPos(double xpos, double ypos) const {
	if (this->window) {
		glfwSetCursorPos(this->window, xpos, ypos);
	}
}

double Window::getScrollXOffset() const {
	return this->scrollXOffset;
}

double Window::getScrollYOffset() const {
	return this->scrollYOffset;
}
