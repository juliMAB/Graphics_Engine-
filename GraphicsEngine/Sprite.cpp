#include "src/Sprite/Sprite.h"

const int tamVerts = 32;//4 * tam1Vert;
const int indicesTam = 6;
Sprite::Sprite(Renderer* render, std::string filePathImage)
{
	std::cout << "-------Create new Sprite:-------"<<std::endl;
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
	_UniformTexLocation = glGetUniformLocation(_renderer->GetShader(), "theTexture");
	uint _useTexture = glGetUniformLocation(_renderer->GetShader(), "useTexture");
	glUniform1i(_useTexture, true);

	_renderer->Setattributes(_posLocation, 2, tam1Vert, 0);
	_renderer->Setattributes(_posColor, 4, tam1Vert, 2);
	baseUVCoords[0] = { 1.0f, 1.0f };
	baseUVCoords[1] = { 1.0f, 0.0f };
	baseUVCoords[2] = { 0.0f, 0.0f };
	baseUVCoords[3] = { 0.0f, 1.0f };

	float UVs[8] =
	{
		baseUVCoords[0].x, baseUVCoords[0].y,
		baseUVCoords[1].x, baseUVCoords[1].y,
		baseUVCoords[2].x, baseUVCoords[2].y,
		baseUVCoords[3].x, baseUVCoords[3].y
	};
	_renderer->CreateExtraBuffer(bufferPosUVs, 1);
	_renderer->BindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	
	
	_renderer->Setattributes(_postexture, 2, tam1Vert, 6);


	_texture = new Texture(filePathImage);
	std::cout  << "-----End Create new Sprite-------"<<std::endl<<std::endl;
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
	_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color,_UniformTexLocation,_texture->_textureID);
	
	_renderer->Draw(indicesTam, _vao);
}
uint Sprite::GetCurrentTextureIDToDraw()
{
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		if (animations[i]->playing)
		{
			if (animations[i]->Update())
			{
				BindCustomUVCoords(i);
				lastCoordIndex = i;
			}
			return animations[i]->GetTexture()->_textureID;
		}
	}
	if (animations.size() > 0) BindCustomUVCoords(lastCoordIndex);
	else BindBaseUVCoords();
	return _texture->_textureID;
}
void Sprite::BindCustomUVCoords(int i)
{
	glm::vec2* uv = animations[i]->getCurrentFramesCoordinates();
	float UVs[8] =
	{
		uv[0].x, uv[0].y, // top right
		uv[1].x, uv[1].y, // bottom right
		uv[2].x, uv[2].y, // bottom left
		uv[3].x, uv[3].y, // top left 
	};
	_renderer->BindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
}
void Sprite::BindBaseUVCoords()
{
	float UVs[8] =
	{
		baseUVCoords[0].x, baseUVCoords[0].y,
		baseUVCoords[1].x, baseUVCoords[1].y,
		baseUVCoords[2].x, baseUVCoords[2].y,
		baseUVCoords[3].x, baseUVCoords[3].y
	};
	_renderer->BindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_STATIC_DRAW);
}