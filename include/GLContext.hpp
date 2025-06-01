#ifndef GLCONTEXT_HPP
#define GLCONTEXT_HPP

#include "Window.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class GLContext
{
private:
	int version;
	Window window;
	// Terminate the OpenGL context
	void terminate();
public:
	GLContext();
	~GLContext();

	void	init();

	Window &getWindow();

	void pollEvents() const;
};

#endif