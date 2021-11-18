#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "../Exports/Exports.h"

#include "../TextureImporter/TextureImporter.h"

typedef unsigned int uint;
class GraficosEngine_API Texture {
private:
	int _width;
	int _height;
	int _bitDepth;
	int _channels;
	unsigned char* _texData;
	std::string _path;
public:
	uint _textureID;
	Texture(const std::string path);
	~Texture();

	uint GetID();
	bool LoadTexture();
	bool LoadTexture(const std::string path);
	void UseTexture();
	void StopTexture();
	void ClearTexture();
};

#endif