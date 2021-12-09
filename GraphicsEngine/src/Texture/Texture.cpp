#include "Texture.h"
#include "../GLEW/glew.h"
#include <iostream>

Texture::Texture(const std::string path,bool flip)
{
	std::cout << "-----Create new Texture-----"<<std::endl;
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
	_channels = 0;
	_path = path;
	if (TextureImporter::LoadTexture(_path, _textureID, _width, _height, _channels, flip))
	{
		std::cout << "Texture load suscefully" << std::endl;
	}
	else
	{
		std::cout << "Texture load FAIL" << std::endl;
	}
	std::cout << "-----End Create new Texture----" << std::endl;
}
Texture::~Texture() {
	glDeleteTextures(1, &_textureID);
	_textureID = 0;
	_width = 0;
	_height = 0;
	_bitDepth = 0;
	_path = " ";
}

bool Texture::LoadTexture(const std::string path, bool flip) {
	_path = path;
	return TextureImporter::LoadTexture(_path, _textureID, _width, _height, _channels, flip);
}
void Texture::UseTexture() {
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}
void Texture::StopTexture() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}