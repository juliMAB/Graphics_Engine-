#ifndef IMPORTER2_H
#define IMPORTER2_H
#define IMPORTER true
#include "Model/Model.h"
#include <STB/stb_image.h>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/postprocess.h>
#include <ASSIMP/scene.h>

namespace JuliEngine
{
	class GraficosEngine_API Importer2 {
	public:
		 void loadModel(Model* theModel, string const& path);
	private:
		 void processNode(aiNode* node, const aiScene* scene, Entity2* currentParent);
		 Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		 vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
		 vector<Texture> textures_loaded;
		 Model* newModel;
		 string directory;
	};
}



#endif