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
	//float* shapeVertices;
	Shape(Renderer* rend, TypeShape typeShape);
	void InitBinds(int vertices);
	void InitShape(int vertices);
	~Shape();
	void Draw();
};

#endif