#ifndef SHAPE_H
#define SHAPE_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include "../Texture/Texture.h"

#define TRIANGLE 0x0004
#define QUAD 0x0007


typedef unsigned int uint;
class GraficosEngine_API Shape : public Entity {
	float* shapeVertices;
	uint _vbo;
	uint _vao;
	uint _ibo;

	uint _textureID;
	int  _width;
	int  _height;
	int  _bitDepth;
	bool _usingTexture;
	Texture* _texture;
public:
	Shape(Renderer* rend, TypeShape typeShape);
	~Shape();
	void InitShape(TypeShape type);
	void DrawShape();
	int GetVerticesArrLenght();
	int GetVerticesTam();
	float* GetVertices();
	float GetVertexIndex(int ind);
	void SetColor(float r, float g, float b);
	void SetColor(float r, float g, float b, float a);
	void SetColor(glm::vec3 color, float alpha);
	void SetColor(glm::vec4 color);
	void LoadTexture(const char* path, const char* name);
	void setShape(glm::vec2 pos, float width, float height);
};

#endif