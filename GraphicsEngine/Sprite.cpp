#include "src/Sprite/Sprite.h"

const int tamVerts = 32;//4 * tam1Vert;
const int indicesTam = 6;
Sprite::Sprite(Renderer* render, std::string filePathImage)
{
	_renderer = render;
	int tam1Vert = 8;
	float vertex [tamVerts]= 
	{
				 // positions             colors                 texture coords
				 0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, //
				 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // 
				-0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, // 
				-0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f  // 
	};
	uint indices [indicesTam]={ 0, 1, 2, 2, 3, 0 };
	
	_renderer->CreateNewBuffers(_vao, _vbo, _ebo);
	_renderer->BindBuffer(_vao, _vbo, _ebo, vertex, sizeof(vertex), indices, sizeof(indices));

	glUseProgram(_renderer->GetShader());
	_uniformPos = glGetUniformLocation(_renderer->GetShader(), "transform");
	_uniformColor = glGetUniformLocation(_renderer->GetShader(), "color");
	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
	_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
	_uniformAlpha = glGetUniformLocation(_renderer->GetShader(), "alpha");
	_texLocation = glGetAttribLocation(_renderer->GetShader(), "theTexture");
	uint _useTexture = glGetUniformLocation(_renderer->GetShader(), "useTexture");
	glUniform1i(_useTexture, true);
	glUseProgram(_renderer->GetShader());

	_renderer->Setattributes(_posLocation, 2, tam1Vert, 0);
	_renderer->Setattributes(_posColor, 4, tam1Vert, 2);
	_renderer->Setattributes(_postexture, 2, tam1Vert, 6);


	_texture = new Texture(filePathImage);
}
Sprite::~Sprite() {
	delete _texture;
	_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	_renderer->DeleteExtraBuffer(1, bufferPosUVs);
	glDeleteTextures(1, &(_texture->_textureID));
}
void Sprite::SetSprite(const std::string path) {
	if (_texture!=NULL)
	{
		_texture->LoadTexture(path);
	}
	else
	{
		_texture = new Texture(path);
	}
}
void Sprite::Draw()
{
	_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color);
	glBindTexture(GL_TEXTURE_2D, _texture->_textureID);
	glUniform1f(_texLocation, (GLfloat)_texture->_textureID);
	_renderer->Draw(indicesTam,_vao);
}