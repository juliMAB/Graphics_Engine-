#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"

class GraficosEngine_API BaseGame {
private:
	Window* _window;
	Renderer* _renderer;
public:
	BaseGame();
	~BaseGame();

	void Awake();
	void Start();
	void Update();
	void Exit();
	
	// --------------------
	Window* GetWindow();
};
#endif