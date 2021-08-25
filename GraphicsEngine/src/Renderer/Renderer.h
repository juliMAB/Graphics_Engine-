#ifndef RENDERER_H
#define RENDERER_H
#include "../Exports/Exports.h"
#include "../Window/Window.h"

class GraficosEngine_API Renderer {
private:
	Window* _window;
public:
	Renderer();
	void Awake(Window* window);
	void Start();
	void Update();
	void Exit();

	// --------------------
	void DrawTriangle(float size);
};
#endif