#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow *window;
public:
	Window();
	Window(GLFWwindow* win);
	~Window();
	
	Window &operator=(const Window &other);

	void init(int width, int height, const char* title);

	GLFWwindow* getHandle() const;

	void swapBuffers() const;
	bool shouldClose() const;
	void setShouldClose(bool value);

	int getKey(int key) const;
};

#endif