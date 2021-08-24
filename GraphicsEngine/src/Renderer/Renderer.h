#ifndef RENDERER_H
#define RENDERER_H
//Renderer:
// limpiar la pantalla
// hacer aparecer un triángulo
//
// Shape
// mudar cuestiones de vertices y todo lo que tiene que ver con el triángulo

#include "../Exports/Exports.h"
#include "../Window/Window.h"

class GraficosEngine_API Renderer {
private:
	Window* window;
	
public:
	void Init(Window* window);
	Renderer();
	~Renderer();
	void SetClearWindow(float r, float g, float b, float a);
	void ClearWindow();
	void SwapBuffers();
	void DrawTriangle(float size);
};

#endif