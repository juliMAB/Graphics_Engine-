#ifndef ENTITY3D_H
#define ENTITY3D_H
#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include "Entity.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Juli/Jinterface.h"
#include <iostream>
#include <list>
#include "Mesh/MyMesh.h"
#include "Importer/Importer.h"


class GraficosEngine_API Entity3D : public Entity
{
public:
	Entity3D();
	Entity3D(Renderer* render, std::string path);
	~Entity3D();
	void draw();
	void deinit();
private:
	std::vector<myMesh> meshes;
};

#endif