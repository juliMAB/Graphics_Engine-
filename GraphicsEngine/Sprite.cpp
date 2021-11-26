#include "src/Sprite/Sprite.h"


const int indicesTam = 6;
const int tamVerts = 32;//4 * tam1Vert;
	float vertex[32] =
	{
		// positions             colors                 texture coords
		0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //
		0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // 
	   -0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // 
	   -0.5f, 0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f  // 
	};
Sprite::Sprite(Renderer* render, std::string filePathImage)
{
	_animation = NULL;
	std::cout << "-------Create new Sprite:-------"<<std::endl;


	_renderer = render;
	int tam1Vert = 8;
	
	uint indices [indicesTam]={ 0, 1, 2, 2, 3, 0 };
	
	_renderer->CreateNewBuffers(_vao, _vbo, _ebo);
	_renderer->BindBuffer(_vao, _vbo, _ebo, vertex, sizeof(vertex), indices, sizeof(indices));

	SetUniforms();

	_renderer->Setattributes(_posLocation, 2, tam1Vert, 0);
	_renderer->Setattributes(_posColor, 4, tam1Vert, 2);
	_renderer->Setattributes(_postexture, 2, tam1Vert, 6);


	_texture = new Texture(filePathImage);

	std::cout  << "-----End Create new Sprite-------"<<std::endl<<std::endl;
}
Sprite::~Sprite() {
	_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	glDeleteTextures(1, &(_texture->_textureID));

	if (_texture != NULL) {
		delete _texture;
		_texture = NULL;
	}
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
void Sprite::SetShader()
{
	glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
	unsigned int colorLoc = glGetUniformLocation(_renderer->GetShader(), "color");
	glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

	unsigned int alphaLoc = glGetUniformLocation(_renderer->GetShader(), "alpha");
	glUniform1fv(alphaLoc, 1, &(color.a));

	unsigned int textureLoc = glGetUniformLocation(_renderer->GetShader(), "theTexture");
	glUniform1f(textureLoc, _texture->_textureID);
}
void Sprite::Draw()
{
	glUseProgram(_renderer->GetShader());
	glEnable(GL_TEXTURE_2D);
	//
	_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color);

	SetShader();
	DrawTexturePart();
	//_renderer->Draw2(indicesTam, _vao,_vbo,_ebo,vertex,tamVerts);

	_renderer->Draw(tamVerts, _vao);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::StartUseAnimation() {
	if (_animation == NULL) {
		_animation = new Animation();
		return;
	}

	std::cout << "The sprite already has animation " << std::endl;
}
void Sprite::AddAnimation(int rows, int cols, float duration)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			_animation->AddFrame(i, j, _texture->_width / cols, _texture->_height / rows, _texture->_width, _texture->_height, duration, rows*cols);
		}
	}
}

void Sprite::UpdateAnimation(float timer)
{
	if (!_animation)
		return;

	_animation->Update(timer);

	int currFrame = _animation->GetCurrentFrame();
	if (currFrame != 0)
	{
		Frame f = _animation->GetFrames()[currFrame];

		float uvCoords[]
		{
			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
			f.GetUVCords()[3].u, f.GetUVCords()[3].v
		};

		vertex[6] = uvCoords[0];
		vertex[14] = uvCoords[2];
		vertex[22] = uvCoords[4];
		vertex[30] = uvCoords[6];

		vertex[7] = uvCoords[1];
		vertex[15] = uvCoords[3];
		vertex[23] = uvCoords[5];
		vertex[31] = uvCoords[7];

		/*render->BindTextureBuffer(VBO, sizeof(uvCoords), uvCoords);
		BindAttrib();*/
	}
}

void Sprite::SetUniforms()
{
	glUseProgram(_renderer->GetShader());
	_uniformPos = glGetUniformLocation(_renderer->GetShader(), "transform");
	_uniformColor = glGetUniformLocation(_renderer->GetShader(), "color");
	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
	_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
	_uniformAlpha = glGetUniformLocation(_renderer->GetShader(), "alpha");
	_UniformTexLocation = glGetUniformLocation(_renderer->GetShader(), "theTexture");
	uint _useTexture = glGetUniformLocation(_renderer->GetShader(), "useTexture");
	glUniform1i(_useTexture, true);
}

void Sprite::DrawTexturePart()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->_textureID);
	glUniform1f(_UniformTexLocation, (GLfloat)_texture->_textureID);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
}
