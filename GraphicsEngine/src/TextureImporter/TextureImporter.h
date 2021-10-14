#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include "../Exports/Exports.h"
#include <string>


typedef unsigned int uint;

class GraficosEngine_API TextureImporter {
public:
	static bool LoadTexture(const std::string& path, const std::string& textureName, unsigned char* data, uint& texture, int width, int height, int channels);
};

#endif