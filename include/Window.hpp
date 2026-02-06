#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window
{
private:
	GLFWwindow *window;
	friend void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	friend class GLContext;

protected:
	double _scrollXOffset = 0.0;
	double _scrollYOffset = 0.0;
	int _width;
	int _height;

public:
	Window(int width, int height);
	Window(GLFWwindow* win);
	~Window();
	
	Window &operator=(const Window &other);

	void init(const char* title);

	GLFWwindow* getHandle() const;

	void swapBuffers() const;
	bool shouldClose() const;
	void setShouldClose(bool value);

	int getKey(int key) const;
	int getMouseButton(int button) const;
	void getCursorPos(double &xpos, double &ypos) const;
	void setCursorPos(double xpos, double ypos) const;

	double getScrollXOffset() const;
	double getScrollYOffset() const;

	int getWidth() const;
	int getHeight() const;
};

#endif