#include "Texture.h"
#include "../GLEW/glew.h"
#include <iostream>

	Texture::Texture(const std::string path, const std::string name) {
		_textureID = 0;
		_width = 0;
		_height = 0;
		_bitDepth = 0;
		_channels = 0;
		_path = path;
		_name = name;
	}
	Texture::~Texture() {
		ClearTexture();
	}
	bool Texture::LoadTexture() {
		return TextureImporter::LoadTexture(_path, _name, _texData, _textureID, _width, _height, _channels);
	}
	bool Texture::LoadTexture(const std::string path, const std::string name) {
		_path = path;
		_name = name;
		return TextureImporter::LoadTexture(_path, _name, _texData, _textureID, _width, _height, _channels);
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

	void Texture::ClearTexture() {
		glDeleteTextures(1, &_textureID);
		_textureID = 0;
		_width = 0;
		_height = 0;
		_bitDepth = 0;
		_path = " ";
	}
