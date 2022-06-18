#ifndef IMPORTER2_H
#define IMPORTER2_H
#define IMPORTER true
#include "Model/Model2.h"
#include <STB/stb_image.h>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/postprocess.h>
#include <ASSIMP/scene.h>

namespace JuliEngine
{
	class GraficosEngine_API Importer2 {
	public:
		void static loadModel(Model2* theModel, string const& path);
		static Model2* newModel;
	private:
		void static processNode(aiNode* node, const aiScene* scene);
		Mesh2 static processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture2> static loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	};
}



#endif