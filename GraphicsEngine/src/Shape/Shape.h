#ifndef SHAPE_H
#define SHAPE_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"

#define TRIANGLE 0x0004
#define QUAD 0x0007


	typedef unsigned int uint;
	class GraficosEngine_API Shape : public Entity {
		float* _vb;
		uint _vbo;
		uint _vao;
		uint _ibo;

		uint vertexColorLocation;
		uint _uniformView;
		uint _uniformProjection;
	public:
		Shape(Renderer* rend);
		~Shape();
		void DrawShape();
		int GetVerticesArrLenght();
		int GetVerticesTam();
		float* GetVertices();
		float GetVertexIndex(int ind);
		void InitShape(TypeShape type, TypeShader t);
	};

#endif