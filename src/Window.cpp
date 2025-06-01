#include "Window.hpp"
#include <stdexcept>
#include <iostream>

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