#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "../Exports/Exports.h"

#include "../TextureImporter/TextureImporter.h"

typedef unsigned int uint;
class GraficosEngine_API Texture {
private:
	int _bitDepth;
	int _channels;
	std::string _path;
public:
	int _width;
	int _height;
	uint _textureID;
	Texture(const std::string path);
	~Texture();

	bool LoadTexture(const std::string path);
	void UseTexture();
	void StopTexture();
};

#endif