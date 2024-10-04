#ifndef GAME_H
#define GAME_H
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
class Game {
public:
	static const int MAX_WINDOWS = 2;
	GLFWwindow* _windows[MAX_WINDOWS];
	Game();
	~Game();
	int Init();
	int Deinit();
	void Update();
	void Draw();
	bool IsRunning();
};
#endif