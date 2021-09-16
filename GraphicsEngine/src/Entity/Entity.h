#ifndef ENTITY_H
#define ENTITY_H
#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include "../GLM/glm.hpp"

struct Triangle {
	glm::vec2 point1;
	glm::vec2 point2;
	glm::vec2 point3;
};

class GraficosEngine_API Entity {
private:
	Renderer* _renderer;
public:
	Renderer* GetRenderer();
	void SetRenderer(Renderer* rend);
	void DrawTriangle(Triangle triangle, Color color);
	void SetTriangle();
};

#endif