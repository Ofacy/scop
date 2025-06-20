#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>


class Window
{
private:
	GLFWwindow *window;
	friend void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	friend class GLContext;

protected:
	double scrollXOffset = 0.0;
	double scrollYOffset = 0.0;

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
	int getMouseButton(int button) const;
	void getCursorPos(double &xpos, double &ypos) const;
	void setCursorPos(double xpos, double ypos) const;

	double getScrollXOffset() const;
	double getScrollYOffset() const;
};

#endif