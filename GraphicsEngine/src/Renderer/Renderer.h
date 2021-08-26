#ifndef RENDERER_H
#define RENDERER_H
#include "../Exports/Exports.h"
#include "../Window/Window.h"

class GraficosEngine_API Renderer {
private:
	Window* _window;
	unsigned int buffer;
public:
	Renderer();
	void Awake(Window* window);
	void Start();
	void Update();
	void Exit();
	void BeginDrawing();
	// --------------------
	void DrawTriangle(float size);
	void SetClearWindow(float r, float g, float b, float a);
};
#endif