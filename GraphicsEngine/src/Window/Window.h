#ifndef WINDOW_H
#define WINDOW_H
struct GLFWwindow;
struct GLFWmonitor;
#include "../Exports/Exports.h"

class GraficosEngine_API Window {
	GLFWwindow* _window;
public:
	Window();
	~Window();
	int MakeWindow(int width, int height, const char* windowName, GLFWmonitor* fullScreen);
	void InitWindow();
	int CheckIfWindowIsOpen();
	void DestroyWindow();
	GLFWwindow* GetWindow();
};

#endif