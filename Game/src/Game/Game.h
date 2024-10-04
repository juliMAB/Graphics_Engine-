#ifndef GAME_H
#define GAME_H
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
class Game {
public:
	Window* _window;
	Game();
	~Game();
	int Init();
	int Deinit();
	void Update();
	void Draw();
	bool IsRunning();
private:
	int WINDOWINIT();
	int WINDOWDEINIT();
};
#endif