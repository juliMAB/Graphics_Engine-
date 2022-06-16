#ifndef ENTITY3D_H
#define ENTITY3D_H
#include "Entity.h"
#include "Entity2/Entity2.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Juli/Jinterface.h"
#include <iostream>
#include <list>
#define IMPORTER false
#include "Importer/Importer.h"




#include "Exports/Exports.h"
#include "Entity/entity.h"
#include <Material/material.h>
#include "Importer/Importer.h"
#include <vector>
namespace JuliEngine
{
	class GraficosEngine_API Entity3D : public Entity2
	{
	public:
		Entity3D(Renderer* render, std::string path);
		~Entity3D() {};
		void draw();
	private:
		std::vector<Mesh> meshes;
	};
}

#endif