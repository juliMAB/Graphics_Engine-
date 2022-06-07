#ifndef IMPORTER_H
#define IMPORTER_H

#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
//#include "Mesh/MyMesh.h"
//#include "Mesh/Mesh.h"
//#include "Model/Model.h"
#include <MyMesh/Mesh.h>
#include <vector>

class GraficosEngine_API Importer {
public:

	Importer();
	~Importer();
	static std::vector<Mesh> loadModel(std::string path);

protected:
private:
	//static myVertex convertType(Vertex vertex);
	//static myTexture convertType(Texture texture);
};
	


#endif