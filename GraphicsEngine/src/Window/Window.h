#ifndef WINDOW_H
#define WINDOW_H
#include "../Exports/Exports.h"
#include <iostream>

class GraficosEngine_API Window {
private:
	GLFWwindow* _window;
public:
	Window();

	void Start();
	void Update();
	void Exit();

	// --------------------
	int MakeWindow(int w, int h, std::string name);
	void PoolEvents();
	GLFWwindow* GetWindow();
	void ResizeWindow(int width, int height);
	void ClearWindow(float r, float g, float b, float a);
};
#endif