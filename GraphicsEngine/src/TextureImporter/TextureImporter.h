#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include "../Exports/Exports.h"
#include <string>


typedef unsigned int uint;
struct textureData
{
	unsigned int ID;
	float width;
	float height;
};
class GraficosEngine_API TextureImporter {
public:
	static bool LoadTexture(const std::string& path, unsigned char* data, uint& texture, int& width, int& height, int& channels);
};

#endif