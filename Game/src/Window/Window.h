#ifndef WINDOW_H
#define WINDOW_H
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
class Window
{
private:
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;

	GLFWwindow* _glfWindow = nullptr;
	//typedef std::function<void()> processInput;
public:
	Window();
	~Window();
	//processInput OnProcessInput;
	void Init(int W, int H, const char* name);
	void PollEvents();
	void SwapBuffers();
	bool WindowShouldClose();
	void SelectWindowAtCurrentContext();
	void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);
};
#endif


