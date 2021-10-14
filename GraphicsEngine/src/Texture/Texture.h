#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "../Exports/Exports.h"

#include "../TextureImporter/TextureImporter.h"

	typedef unsigned int uint;
	class GraficosEngine_API Texture {
		uint _textureID;
		int _width;
		int _height;
		int _bitDepth;
		int _channels;
		unsigned char* _texData;
		std::string _path;
		std::string _name;
	public:
		Texture(const std::string path, const std::string name);
		~Texture();
		bool LoadTexture();
		bool LoadTexture(const std::string path, const std::string name);
		void UseTexture();
		void StopTexture();
		void ClearTexture();

	};

#endif