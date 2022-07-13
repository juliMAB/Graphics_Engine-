#ifndef ENTITY3D_H
#define ENTITY3D_H
//#include "Entity.h"
#include "Entity2/Entity2.h"
#define IMPORTER false
#include "Importer/Importer2.h"
#include "Model/Model.h"
#include <Material/material.h>
namespace JuliEngine
{
	class GraficosEngine_API Entity3D
	{
	public:
		Entity3D(Renderer* render, std::string path);
		~Entity3D() {};
		Model* model;
	private:
	};
}

#endif