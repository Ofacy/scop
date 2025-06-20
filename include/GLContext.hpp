#ifndef GLCONTEXT_HPP
#define GLCONTEXT_HPP

#include "Window.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class GLContext
{
	
private:
	static GLContext *instance;
	Window window;
	// Terminate the OpenGL context
	void terminate();
	GLContext();
public:
	static GLContext &getInstance();
	~GLContext();

	void	init();
	Window &getWindow();
	void pollEvents();
};

#endif