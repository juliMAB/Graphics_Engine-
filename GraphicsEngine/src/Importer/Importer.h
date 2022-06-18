#ifndef IMPORTER_H
#define IMPORTER_H
#define IMPORTER true
#include "../Renderer/Renderer.h"
#include <MyMesh/Mesh.h>
#include <vector>
#include "Model/Model2.h"

namespace JuliEngine
{
	class GraficosEngine_API Importer {
	public:
		Model2 static LoadModel(string path);
	};
}
	


#endif