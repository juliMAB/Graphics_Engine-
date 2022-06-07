#include "Importer.h"
#include <Model/Model.h>

Importer::Importer()
{
}

Importer::~Importer()
{
}

std::vector<Mesh> Importer::loadModel(std::string path)
{
	Model* newModel = new Model(path);

	vector<Mesh> meshes;

	vector<Mesh> importerMeshes = newModel->GetMeshes();

	return newModel->GetMeshes();
}