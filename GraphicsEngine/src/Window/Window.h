#ifndef WINDOW_H
#define WINDOW_H
#include "../Exports/Exports.h"

class GraficosEngine_API Window {
private:
	GLFWwindow* _window;
public:
	Window();

	void Awake();
	void Start();
	void Update();
	void Exit();

	// --------------------
	void SwapBuffers();
	void PoolEvents();
	GLFWwindow* GetWindow();
	void ResizeWindow(int width, int height);
};
#endif