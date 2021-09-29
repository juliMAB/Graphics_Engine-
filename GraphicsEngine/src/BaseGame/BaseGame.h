#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "../Renderer/Renderer.h"
#include "../Input/Input.h"
#include "../Shape/Shape.h"
class GraficosEngine_API BaseGame {
private:
	Window* _window;
	Renderer* _renderer;
	
	void UpdateEngine();
	bool GlewStart();
	void Exit();
	Window* GetWindow();
public:
	Renderer* GetRenderer();
	BaseGame();
	~BaseGame();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

	int StartEngine(int width, int height, const char* windowName);
	bool IsKeyDown(Input::KeyCode key);
	bool IsKeyRelease(Input::KeyCode key);
	bool IsKeyUp(Input::KeyCode key);
	void ClearWindow(float r, float g, float b, float a);
	// --------------------
};
#endif