#ifndef SHAPE_H
#define SHAPE_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include "../Texture/Texture.h"
#include "../Entity2D/Entity2D.h"

#define TRIANGLE 0x0004
#define QUAD 0x0007


typedef unsigned int uint;
class GraficosEngine_API Shape : public Entity2D {
public:
	float* shapeVertices;
	uint* indices;
	//float* shapeVertices;
	Shape(Renderer* rend, TypeShape typeShape);
	void initVerts(int vertices);
	void ultraHack(int indice, float value);
	float ultraHackGetValue(int indice);
	void InitBinds(int vertices);
	void CrazyFunc();
	void InitShape(int vertices);
	~Shape();
	void Draw();
	void DrawDebug();
	void ConsoleData();
};

#endif