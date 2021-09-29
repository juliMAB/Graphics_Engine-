#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "../Renderer/Renderer.h"
#include "../Input/Input.h"
#include "../Shape/Shape.h"
class GraficosEngine_API BaseGame {
private:
	Window* _window;
	Renderer* _renderer;
public:
	BaseGame();
	~BaseGame();

	void Awake();
	int StartEngine(int width, int height, const char* windowName);
	void UpdateEngine();
	virtual void Start() = 0;
	bool GlewStart();
	virtual void Update() = 0;
	void virtual End() = 0;

	void Exit();
	
	// --------------------
	Window* GetWindow();
	Renderer* GetRenderer();
};
#endif