#ifndef IMPORTER_H
#define IMPORTER_H
#define IMPORTER true
#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include <MyMesh/Mesh.h>
#include <vector>

class GraficosEngine_API Importer {
public:

	Importer();
	~Importer();
	static std::vector<Mesh> loadModel(std::string path);

protected:
private:

};
	


#endif